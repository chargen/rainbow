// Copyright (c) 2010-15 Bifrost Entertainment AS and Tommy Nguyen
// Distributed under the MIT License.
// (See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT)

#ifndef INPUT_POINTER_H_
#define INPUT_POINTER_H_

/// A pointer event.
struct Pointer
{
	unsigned int hash;        ///< Unique hash value for each pointer.
	int x, y;                 ///< Position of pointer.
	unsigned long timestamp;  ///< The relative time at which this event occurred, in milliseconds.

	Pointer() : hash(0), x(0), y(0), timestamp(0) {}

	Pointer(const unsigned int hash,
	        const int x,
	        const int y,
	        const unsigned long t)
	    : hash(hash), x(x), y(y), timestamp(t) {}

	/// Two pointer events are equal if their hash values are; i.e. they share a
	/// common origin.
	friend bool operator==(const Pointer &a, const Pointer &b)
	{
		return a.hash == b.hash;
	}
};

#endif