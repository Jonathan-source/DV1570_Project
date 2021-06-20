#include "LuaEngine.h"

#include <cassert>

lua_State* LuaEngine::L() const
{
	return this->m_L;
}

void LuaEngine::ExecuteFile(const char* file)
{
	assert(file);
	CheckLua(luaL_dofile(this->m_L, file));
}

void LuaEngine::ExecuteString(const char* expression)
{
	assert(expression);
	CheckLua(luaL_dostring(m_L, expression));
}

bool LuaEngine::CheckLua(int state) const
{
	if(state != LUA_OK)
	{
		std::string errorMsg = lua_tostring(this->m_L, -1);
		luaL_error(this->m_L, "Error: %s", errorMsg.c_str());
		return false;
	}
	return true;
}
