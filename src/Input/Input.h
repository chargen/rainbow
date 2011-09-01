#ifndef INPUT_H_
#define INPUT_H_

#include "Common/Vector.h"
#include "Input/Acceleration.h"
#include "Input/Touchable.h"

#define RAINBOW_ALL_EVENTS    -1
#define RAINBOW_KEY_EVENTS    (1 << 0)
#define RAINBOW_TOUCH_EVENTS  (1 << 1)

/// Handles accelerometer/gyroscope and touch events independent of platform.
///
/// Subscribable input events. There are no accelerometer events.
///
/// \see http://developer.apple.com/library/ios/#documentation/UIKit/Reference/UIAcceleration_Class/Reference/UIAcceleration.html
///
/// Copyright 2010-11 Bifrost Games. All rights reserved.
/// \author Tommy Nguyen
class Input
{
public:
	static Input& Instance();

	bool accelerated;           ///< Whether we should update accelerometer data
	Acceleration acceleration;  ///< Accelerometer data

	/// Subscribe to input events.
	/// \param t      The object that wants to subscribe
	/// \param flags  Events to subscribe to
	void subscribe(Touchable *const t, unsigned int flags);

	void touch_began(Touch *const touches, const unsigned int count);
	void touch_canceled();
	void touch_ended(Touch *const touches, const unsigned int count);
	void touch_moved(Touch *const touches, const unsigned int count);

private:
	Vector<Touchable *> touch_subscribers;

	Input() { }

	/// Intentionally left undefined.
	Input(const Input &);

	/// The coordinates system on most devices are "flipped". This function
	/// will "correct" the values.
	void touch_flip(Touch *const touches, const unsigned int count);

	/// Intentionally left undefined.
	Input& operator=(const Input &);
};

inline Input& Input::Instance()
{
	static Input i;
	return i;
}

#endif
