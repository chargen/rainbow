// Copyright (c) 2010-14 Bifrost Entertainment AS and Tommy Nguyen
// Distributed under the MIT License.
// (See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT)

#ifndef COMMON_SHAREDPTR_H_
#define COMMON_SHAREDPTR_H_

#include "Common/Debug.h"
#include "Common/NonCopyable.h"

/// Makes a class reference countable.
///
/// Subclasses of RefCounted can be wrapped with SharedPtr.
class RefCounted : private NonCopyable<RefCounted>
{
	template<class T> friend class SharedPtr;

protected:
	RefCounted() : refs(0) { }
	~RefCounted() = default;

private:
	unsigned int refs;
};

/// Shared pointers automatically release the allocated memory when it no longer
/// is referenced.
///
/// Classes that need to be shared this way must subclass RefCounted.
template<class T>
class SharedPtr
{
public:
	/// Constructs an empty shared pointer.
	SharedPtr();

	/// Copies pointer and increments its reference counter.
	SharedPtr(const SharedPtr<T> &);

	/// Takes over pointer. Does not increase its reference count and will leave
	/// the other pointer empty.
	SharedPtr(SharedPtr<T> &&);

	/// Sets pointer and increment its reference counter.
	explicit SharedPtr(T *);

	~SharedPtr();

	/// Returns pointer to the managed object.
	inline T* get() const;

#ifdef RAINBOW_TEST
	/// Returns the number of references to this object.
	unsigned int ref_count() const { return this->ptr->refs; }
#endif

	/// Returns whether there is an associated managed object.
	explicit operator bool() const;

	/// Releases the current pointer and retains the new one.
	SharedPtr<T>& operator=(const SharedPtr<T> &);

	/// Releases the current pointer and takes over the new one.
	SharedPtr<T>& operator=(SharedPtr<T> &&);

	/// Releases the current pointer and assigns the new one.
	SharedPtr<T>& operator=(T *);

	/// Dereferences pointer to the managed object.
	inline T& operator*() const;

	/// Dereferences pointer to the managed object.
	inline T* operator->() const;

private:
	RefCounted *ptr;  ///< Actual pointer managed by this shared pointer.

	/// Decrements reference counter and releases memory if the count hits 0.
	void release();
};

template<class T>
SharedPtr<T>::SharedPtr() : ptr(nullptr) { }

template<class T>
SharedPtr<T>::SharedPtr(const SharedPtr<T> &shared_ptr) : ptr(shared_ptr.ptr)
{
	if (!this->ptr)
		return;

	++this->ptr->refs;
}

template<class T>
SharedPtr<T>::SharedPtr(SharedPtr<T> &&shared_ptr) : ptr(shared_ptr.ptr)
{
	shared_ptr.ptr = nullptr;
}

template<class T>
SharedPtr<T>::SharedPtr(T *ptr) : ptr(ptr)
{
	R_ASSERT(this->ptr, "No reference to pointer");
	++this->ptr->refs;
}

template<class T>
SharedPtr<T>::~SharedPtr()
{
	this->release();
}

template<class T>
T* SharedPtr<T>::get() const
{
	return static_cast<T*>(this->ptr);
}

template<class T>
SharedPtr<T>::operator bool() const
{
	return this->ptr;
}

template<class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T> &shared_ptr)
{
	return *this = static_cast<T*>(shared_ptr.ptr);
}

template<class T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T> &&shared_ptr)
{
	this->release();
	this->ptr = shared_ptr.ptr;
	shared_ptr.ptr = nullptr;
	return *this;
}

template<class T>
SharedPtr<T>& SharedPtr<T>::operator=(T *ptr)
{
	if (ptr == this->ptr)
		return *this;
	this->release();
	this->ptr = ptr;
	if (!this->ptr)
		return *this;
	++this->ptr->refs;
	return *this;
}

template<class T>
T& SharedPtr<T>::operator*() const
{
	R_ASSERT(this->ptr, "No reference to pointer");
	return *static_cast<T*>(this->ptr);
}

template<class T>
T* SharedPtr<T>::operator->() const
{
	R_ASSERT(this->ptr, "No reference to pointer");
	return static_cast<T*>(this->ptr);
}

template<class T>
void SharedPtr<T>::release()
{
	R_ASSERT(!this->ptr || this->ptr->refs > 0,
	         "This object should've been deleted by now");

	if (this->ptr && !--this->ptr->refs)
	{
		delete static_cast<T*>(this->ptr);
		this->ptr = nullptr;
	}
}

#endif
