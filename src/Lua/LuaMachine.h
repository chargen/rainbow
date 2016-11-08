// Copyright (c) 2010-16 Bifrost Entertainment AS and Tommy Nguyen
// Distributed under the MIT License.
// (See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT)

#ifndef LUA_LUAMACHINE_H_
#define LUA_LUAMACHINE_H_

#include <cstdint>

#include "Common/NonCopyable.h"
#include "Common/Passkey.h"

class Data;
class LuaScript;
struct lua_State;

namespace rainbow
{
    namespace lua { class SceneGraph; }

    class SceneNode;

    /// <summary>Embeds Lua scripting engine.</summary>
    class LuaMachine : private NonCopyable<LuaMachine>
    {
    public:
        LuaMachine(const Passkey<LuaScript>&);
        ~LuaMachine();

        /// <summary>Initialises a new Lua state.</summary>
        auto init(LuaScript* instance, SceneNode* root) -> int;

        /// <summary>Uninitialises current Lua state and closes it.</summary>
        void close();

        /// <summary>Loads and initialises game script.</summary>
        auto start(const Data& main) -> int;

        /// <summary>Calls game update function.</summary>
        auto update(uint64_t t) -> int;

        operator lua_State*() const { return state_; }

    private:
        lua_State* state_;
        int internal_;
        int traceback_;
        lua::SceneGraph* scenegraph_;
    };
}

#endif
