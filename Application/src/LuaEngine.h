#pragma once
extern "C"
{
#include "../Lua542/include/lua.h"
#include "../Lua542/include/lauxlib.h"
#include "../Lua542/include/lualib.h"
}

#pragma comment(lib, "../Lua542/liblua54.a")
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

