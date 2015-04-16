// Copyright (c) 2010-14 Bifrost Entertainment AS and Tommy Nguyen
// Distributed under the MIT License.
// (See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT)

#include "Lua/lua_Input.h"

#include "Input/Input.h"
#include "Input/Key.h"
#include "Input/Touch.h"
#include "Lua/LuaHelper.h"

NS_RAINBOW_LUA_MODULE_BEGIN(input)
{
	namespace
	{
		enum Event
		{
			kEventKeyDown,
			kEventKeyUp,
			kEventTouchBegan,
			kEventTouchCanceled,
			kEventTouchEnded,
			kEventTouchMoved
		};

		int acceleration = -1;
		int events = -1;
		size_t event_count = -1;

		const char *const kInputEvents[] = {
			"key_down",
			"key_up",
			"touch_began",
			"touch_canceled",
			"touch_ended",
			"touch_moved"
		};

		void push_event(lua_State *L, const Event event)
		{
			lua_rawgeti(L, LUA_REGISTRYINDEX, events);
			lua_pushinteger(L, ++event_count);
			lua_rawseti(L, -2, 0);

			lua_rawgeti(L, -1, event_count);
			if (lua_type(L, -1) != LUA_TTABLE)
			{
				lua_pop(L, 1);
				lua_createtable(L, 2, 0);
				lua_pushvalue(L, -1);
				lua_rawseti(L, -3, event_count);
			}
			lua_pushstring(L, kInputEvents[event]);
			lua_rawseti(L, -2, 1);
		}

#ifdef RAINBOW_BUTTONS

		void on_key_event(lua_State *L, const Event event, const Key &key)
		{
			push_event(L, event);

			lua_createtable(L, 2, 0);
			lua_pushinteger(L, static_cast<lua_Integer>(key.key));
			lua_rawseti(L, -2, 1);
			lua_pushinteger(L, key.modifier);
			lua_rawseti(L, -2, 2);

			lua_rawseti(L, -2, 2);
			lua_pop(L, 2);
		}

#endif  // RAINBOW_BUTTONS

		void on_touch_event(lua_State *L,
		                    const Event event,
		                    const unsigned int count,
		                    const Touch *const touches)
		{
			push_event(L, event);

			if (!count)
				lua_pushnil(L);
			else
			{
				lua_createtable(L, 0, count);
				for (unsigned int i = 0; i < count; ++i)
				{
					lua_pushinteger(L, touches[i].hash);
					lua_createtable(L, 0, 5);
					luaR_rawsetinteger(L, "x", touches[i].x);
					luaR_rawsetinteger(L, "y", touches[i].y);
					luaR_rawsetinteger(L, "x0", touches[i].x0);
					luaR_rawsetinteger(L, "y0", touches[i].y0);
					luaR_rawsetinteger(L, "timestamp", touches[i].timestamp);
					lua_rawset(L, -3);
				}
			}

			lua_rawseti(L, -2, 2);
			lua_pop(L, 2);
		}
	}

	void init(lua_State *L)
	{
		lua_pushliteral(L, "input");
		lua_createtable(L, 0, 11);

		// rainbow.input.acceleration
		lua_pushliteral(L, "acceleration");
		lua_createtable(L, 0, 4);
		lua_pushvalue(L, -1);
		acceleration = luaL_ref(L, LUA_REGISTRYINDEX);
		lua_rawset(L, -3);

		lua_pushliteral(L, "__events");
		lua_createtable(L, 0, 0);
		lua_pushvalue(L, -1);
		events = luaL_ref(L, LUA_REGISTRYINDEX);
		lua_rawset(L, -3);

		lua_rawset(L, -3);
		clear(L);
	}

	void accelerated(lua_State *L, const Acceleration &a)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, acceleration);
		luaR_rawsetnumber(L, "x", a.x());
		luaR_rawsetnumber(L, "y", a.y());
		luaR_rawsetnumber(L, "z", a.z());
		luaR_rawsetnumber(L, "timestamp", a.timestamp());
		lua_pop(L, 1);
	}

	void clear(lua_State *L)
	{
		if (event_count == 0)
			return;

		lua_rawgeti(L, LUA_REGISTRYINDEX, events);
		lua_pushinteger(L, 0);
		lua_rawseti(L, -2, 0);
		lua_pop(L, 1);
		event_count = 0;
	}

#ifdef RAINBOW_BUTTONS

	void on_key_down(lua_State *L, const Key &key)
	{
		on_key_event(L, kEventKeyDown, key);
	}

	void on_key_up(lua_State *L, const Key &key)
	{
		on_key_event(L, kEventKeyUp, key);
	}

#endif  // RAINBOW_BUTTONS

	void on_touch_began(lua_State * L,
	                    const unsigned int count,
	                    const Touch *const touches)
	{
		on_touch_event(L, kEventTouchBegan, count, touches);
	}

	void on_touch_canceled(lua_State * L)
	{
		on_touch_event(L, kEventTouchCanceled, 0, nullptr);
	}

	void on_touch_ended(lua_State * L,
	                    const unsigned int count,
	                    const Touch *const touches)
	{
		on_touch_event(L, kEventTouchEnded, count, touches);
	}

	void on_touch_moved(lua_State * L,
	                    const unsigned int count,
	                    const Touch *const touches)
	{
		on_touch_event(L, kEventTouchMoved, count, touches);
	}
}
NS_RAINBOW_LUA_MODULE_END(input)
