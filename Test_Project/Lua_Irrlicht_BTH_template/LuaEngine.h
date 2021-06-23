#pragma once
#include "lua.hpp"
#include <string>

class LuaEngine
{
public:
    LuaEngine() : m_L(luaL_newstate()) { luaL_openlibs(m_L); }
    LuaEngine(const LuaEngine& other) = delete;   
    LuaEngine& operator=(const LuaEngine&) = delete; 
    virtual ~LuaEngine() { lua_close(m_L); }       

    // Returns lua_state object.
    lua_State* L() const;

    // Execute Lua File.
    void ExecuteFile(const char* file);

    // Execute Lua Expression (contained in string).
    void ExecuteString(const char* expression);

private:
    lua_State* m_L = nullptr;

private:

    // Handle errors.
    bool CheckLua(int state) const;
};

