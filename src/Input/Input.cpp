// Copyright (c) 2010-15 Bifrost Entertainment AS and Tommy Nguyen
// Distributed under the MIT License.
// (See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT)

#include "Input/Input.h"

#include <utility>

#include "Input/Key.h"

void Input::subscribe(InputListener *const i)
{
	last_listener_->append(i);
	last_listener_ = i;
}

void Input::unsubscribe(InputListener *const i)
{
	i->pop();
}

void Input::accelerated(const double x, const double y, const double z, const double t)
{
	acceleration_.update(x, y, z, t);
}

#ifdef RAINBOW_BUTTONS
void Input::on_key_down(const Key &k)
{
	if (for_each(next(), [&k](InputListener *i) { return i->on_key_down(k); }))
		return;
}

void Input::on_key_up(const Key &k)
{
	if (for_each(next(), [&k](InputListener *i) { return i->on_key_up(k); }))
		return;
}
#endif

void Input::on_touch_began(const unsigned int count, Touch *const touches)
{
	auto began = [count, touches](InputListener *i) {
		return i->on_touch_began(count, touches);
	};
	if (for_each(next(), std::move(began)))
		return;
}

void Input::on_touch_canceled()
{
	auto canceled = [](InputListener *i) { return i->on_touch_canceled(); };
	if (for_each(next(), std::move(canceled)))
		return;
}

void Input::on_touch_ended(const unsigned int count, Touch *const touches)
{
	auto ended = [count, touches](InputListener *i) {
		return i->on_touch_ended(count, touches);
	};
	if (for_each(next(), std::move(ended)))
		return;
}

void Input::on_touch_moved(const unsigned int count, Touch *const touches)
{
	auto moved = [count, touches](InputListener *i) {
		return i->on_touch_moved(count, touches);
	};
	if (for_each(next(), std::move(moved)))
		return;
}

void Input::on_end_link_removed(Link *node)
{
	last_listener_ = static_cast<InputListener*>(node)->prev();
}
