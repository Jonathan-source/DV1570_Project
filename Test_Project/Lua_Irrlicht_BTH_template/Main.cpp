#pragma comment(lib, "Irrlicht.lib")
#ifdef _DEBUG
#pragma comment(lib, "LuaLibd.lib")
#else
#pragma comment(lib, "Lualib.lib")
#endif

#include <lua.hpp>
#include <Windows.h>
#include <iostream>
#include <thread>
#include "lua.hpp"
#include <irrlicht.h>

// Custom Lua class.
#include "LuaEngine.h"

void ConsoleThread(lua_State* L) {
	char command[1000];
	while (GetConsoleWindow()) {
		memset(command, 0, 1000);
		std::cin.getline(command, 1000);
		if (luaL_loadstring(L, command) || lua_pcall(L, 0, 0, 0))
			std::cout << lua_tostring(L, -1) << '\n';
	}
}

int main()
{
	LuaEngine* pLuaEngine = new LuaEngine();
	std::thread conThread(ConsoleThread, pLuaEngine->L());

	// Window data.
	int windowWidth = 1920;
	int windowHeight = 1080;

	// Test: load window config from Lua.
	pLuaEngine->ExecuteFile("C:/Dev/Lua_Irrlicht_BTH_template/Scripts/window_config.lua");
	{
		lua_getglobal(pLuaEngine->L(), "config_table");
		if (lua_istable(pLuaEngine->L(), -1))
		{
			lua_getfield(pLuaEngine->L(), -1, "window_width");
			lua_getfield(pLuaEngine->L(), -2, "window_height");

			windowWidth = (int)lua_tonumber(pLuaEngine->L(), -2);	// Width was put on the stack first, so it has idx -2.
			windowHeight = (int)lua_tonumber(pLuaEngine->L(), -1);	// Height was put on the stack last, so it has idx -1.
		}
	}

	/*
		Ideally each object you want to expose would implement its own version of this method:
		static void register_lua(lua_State* L);
		//register person class into lua script engine
		Person::register_lua(engine->L());
	 */

	irr::SIrrlichtCreationParameters params;
	params.DriverType = irr::video::EDT_SOFTWARE;
	params.WindowSize = irr::core::dimension2d<irr::u32>(windowWidth, windowHeight);
	params.Vsync = true;
	params.AntiAlias = 8;
	irr::IrrlichtDevice* device = createDeviceEx(params);
	if (!device)
		return 1;

	device->setWindowCaption(L"Test_Project");
	irr::video::IVideoDriver* driver = device->getVideoDriver();
	irr::scene::ISceneManager* smgr = device->getSceneManager();
	irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();


	while (device->run()) {
		driver->beginScene(true, true, irr::video::SColor(255, 90, 101, 140));

		smgr->drawAll();
		guienv->drawAll();

		driver->endScene();
	}

	device->drop();
	conThread.join();
	delete pLuaEngine;
	
	return EXIT_SUCCESS;
}