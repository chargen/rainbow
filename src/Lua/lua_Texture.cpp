// Copyright (c) 2010-present Bifrost Entertainment AS and Tommy Nguyen
// Distributed under the MIT License.
// (See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT)

#include "Lua/lua_Texture.h"

#include <lua.hpp>

#include "FileSystem/FileSystem.h"

NS_RAINBOW_LUA_BEGIN
{
    constexpr bool Texture::is_constructible;

    const char Texture::class_name[] = "texture";

    const luaL_Reg Texture::functions[]{
        {"create",  &Texture::create},
        {"trim",    &Texture::trim},
        {nullptr,   nullptr}};

    Texture::Texture(lua_State* L)
    {
        // rainbow.texture("/path/to/texture")
        checkargs<char*>(L);

        const auto path = rainbow::filesystem::relative(lua_tostring(L, 1));
        texture_ = make_shared<TextureAtlas>(path);
        if (!texture_->is_valid())
            luaL_error(L, "rainbow.texture: Failed to create texture");
    }

    SharedPtr<TextureAtlas> Texture::get() const { return texture_; }

    int Texture::create(lua_State* L)
    {
        // <texture>:create(x, y, width, height)
        checkargs<Texture, lua_Number, lua_Number, lua_Number, lua_Number>(L);

        Texture* self = Bind::self(L);
        if (self == nullptr)
            return 0;

        const int x = lua_tointeger(L, 2);
        const int y = lua_tointeger(L, 3);
        const int w = lua_tointeger(L, 4);
        const int h = lua_tointeger(L, 5);
        lua_pushinteger(L, self->texture_->add_region(x, y, w, h));
        return 1;
    }

    int Texture::trim(lua_State* L)
    {
        Texture* self = Bind::self(L);
        if (self == nullptr)
            return 0;

        self->texture_->trim();
        return 0;
    }
} NS_RAINBOW_LUA_END
