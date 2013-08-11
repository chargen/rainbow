#ifndef GRAPHICS_ANIMATION_H_
#define GRAPHICS_ANIMATION_H_

#include "Common/ChronoTrigger.h"
#include "Common/Constants.h"
#include "Common/NonCopyable.h"

class Sprite;

/// Sprite animation using sprite sheets.
///
/// Copyright 2011-13 Bifrost Entertainment. All rights reserved.
/// \author Tommy Nguyen
class Animation : public ChronoTrigger, private NonCopyable<Animation>
{
public:
	static const unsigned int kAnimationEnd = kMaxInt;

	/// \param s       The sprite to animate.
	/// \param frames  Null-terminated array of texture ids to be used as frames.
	/// \param fps     Frames per second.
	/// \param delay   Number of ticks to delay before the animation loops. Negative numbers disable looping.
	inline Animation(Sprite *s, const unsigned int *const frames,
	                 const unsigned int fps, const int delay = 0);

	virtual ~Animation();

	/// Resets sprite animation.
	inline void reset();

	/// Sets number of ticks to delay before the animation loops. Negative
	/// numbers disable looping.
	inline void set_delay(const int delay);

	/// Sets animation frames.
	/// \note This method takes ownership of the array.
	/// \param frames  Null-terminated array of texture ids to be used as frames.
	void set_frames(const unsigned int *const frames);

	inline void set_sprite(Sprite *);

private:
	int delay;                   ///< Number of ticks to delay before the animation loops. Negative numbers disable looping.
	int idled;                   ///< Number of ticks idled.
	const unsigned int *frame;   ///< Current frame.
	const unsigned int *frames;  ///< Null-terminated array of texture ids to be used as frames.
	Sprite *sprite;              ///< The sprite to animate.

	virtual void tick_impl() override;
};

Animation::Animation(Sprite *s, const unsigned int *const fs, const unsigned int fps, const int d) :
	ChronoTrigger(1000.0f / fps), delay(d), idled(0), frame(fs), frames(fs), sprite(s) { }

void Animation::reset()
{
	this->frame = this->frames;
	this->idled = 0;
}

void Animation::set_delay(const int delay)
{
	this->delay = delay;
}

void Animation::set_sprite(Sprite *s)
{
	this->sprite = s;
}

#endif
