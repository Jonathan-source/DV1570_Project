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

// Custom Classes.
#include "LuaEngine.h"
#include "Config.h"


void ConsoleThread(lua_State* L) {
	char command[1000];
	while (GetConsoleWindow()) {
		memset(command, 0, 1000);
		std::cin.getline(command, 1000);
		if (luaL_loadstring(L, command) || lua_pcall(L, 0, 0, 0))
			std::cout << lua_tostring(L, -1) << '\n';
	}
}

void DumpStack(lua_State* L)
{
	std::cout << "------- STACK DUMP -------\n";
	for (int i = lua_gettop(L); i > 0; i--)
	{
		std::cout << "Index " << i << ": " << lua_typename(L, lua_type(L, i)) << "\n";
	}
	std::cout << "--------------------------\n";
}

// Jesus Fuck...
void loadConfig(LuaEngine* pLuaEngine, engine_config_t &config)
{
	pLuaEngine->ExecuteFile("C:/Dev/DV1570_Project/Test_Project/Scripts/engine_config.lua");
	{
		lua_getglobal(pLuaEngine->L(), "config");
		if (lua_istable(pLuaEngine->L(), -1))
		{
			lua_pushstring(pLuaEngine->L(), "title");			
			lua_gettable(pLuaEngine->L(), -2);
			config.title = (irr::core::stringw)lua_tostring(pLuaEngine->L(), -1);
			lua_pop(pLuaEngine->L(), 1);

			lua_pushstring(pLuaEngine->L(), "fullscreen");
			lua_gettable(pLuaEngine->L(), -2);
			config.fullscreen = (bool)lua_toboolean(pLuaEngine->L(), -1);
			lua_pop(pLuaEngine->L(), 1);

			lua_pushstring(pLuaEngine->L(), "vSync");
			lua_gettable(pLuaEngine->L(), -2);
			config.vSync = (bool)lua_toboolean(pLuaEngine->L(), -1);
			lua_pop(pLuaEngine->L(), 1);

			lua_pushstring(pLuaEngine->L(), "antiAlias");
			lua_gettable(pLuaEngine->L(), -2);
			config.antiAlias = (int)lua_tonumber(pLuaEngine->L(), -1);
			lua_pop(pLuaEngine->L(), 1);			
			
			lua_pushstring(pLuaEngine->L(), "resolution");
			lua_gettable(pLuaEngine->L(), -2);
			if (lua_istable(pLuaEngine->L(), -1))
			{				
				lua_pushstring(pLuaEngine->L(), "window_width");
				lua_gettable(pLuaEngine->L(), -2);
				config.window_width = (int)lua_tonumber(pLuaEngine->L(), -1);
				lua_pop(pLuaEngine->L(), 1);
				
				lua_pushstring(pLuaEngine->L(), "window_height");
				lua_gettable(pLuaEngine->L(), -2);
				config.window_height = (int)lua_tonumber(pLuaEngine->L(), -1);
				lua_pop(pLuaEngine->L(), 1);
			}
		}
		
		DumpStack(pLuaEngine->L());
	}
}


int main()
{
	LuaEngine * pLuaEngine = new LuaEngine();
	std::thread conThread(ConsoleThread, pLuaEngine->L());

	// Load engine configurations.
	engine_config_t config;
	loadConfig(pLuaEngine, config);
	
	irr::SIrrlichtCreationParameters params;
	params.DriverType = irr::video::EDT_SOFTWARE;
	params.WindowSize = irr::core::dimension2d<irr::u32>(config.window_width, config.window_height);
	params.Fullscreen = config.fullscreen;
	params.Vsync = config.vSync;
	params.AntiAlias = config.antiAlias;
	irr::IrrlichtDevice* device = createDeviceEx(params);
	if (!device)
		return EXIT_FAILURE;

	device->setWindowCaption(config.title.c_str());
	irr::video::IVideoDriver* driver = device->getVideoDriver();
	irr::scene::ISceneManager* sceneManager = device->getSceneManager();
	irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

	//
	// ADDING CAMERA.
	//
	irr::scene::ICameraSceneNode* camera = sceneManager->addCameraSceneNode();
	camera->setPosition(irr::core::vector3df(0, 0, 5));
	camera->setTarget(irr::core::vector3df(0, 0, 0));
	
	//
	// ADDING MESH.
	//
	// Load mesh & texture
	irr::scene::IMesh* monkey = sceneManager->getMesh("C:/Dev/DV1570_Project/Test_Project/Assets/Monkey.obj");
	irr::video::ITexture * texture = driver->getTexture("C:/Dev/DV1570_Project/Test_Project/Assets/Texture_Monkey.png");

	// Add mesh to scene
	auto meshSceneNode = sceneManager->addMeshSceneNode(monkey);
	
	// Set meshNode material texture
	meshSceneNode->setMaterialTexture(0, texture);

	// Set material type. Change to support eg. transparency
	meshSceneNode->setMaterialType(irr::video::EMT_SOLID);

	// Set position/rotation/scale
	int rotX = 0;
	int rotY = 0;
	int rotZ = 0;
	meshSceneNode->setPosition(irr::core::vector3df(0, 0, 0));
	meshSceneNode->setRotation(irr::core::vector3df(10, 20, 0));


	//
	// ADD BUTTON.
	//
	int anchorX = 0;
	int anchorY = 0;
	int width = 100;
	int height = 100;

	wchar_t text[] = L"Click Here";
	irr::gui::IGUIButton* button = guienv->addButton(irr::core::rect<irr::s32>(anchorX, anchorY, anchorX + width, anchorY + height), nullptr, 0, text);

	
	//
	// ADD LIGHT.
	//
	irr::scene::ILightSceneNode* dirLight = sceneManager->addLightSceneNode(nullptr, irr::core::vector3df(-1.0f, 1.0f, 0.0f), irr::video::SColorf(1.0f, 0.0f, 1.0f));
	dirLight->setLightType(irr::video::ELT_DIRECTIONAL);
	dirLight->setRotation(irr::core::vector3df(90.0f, 0.0f, 0.0f));

	
	//
	// MAIN LOOP.
	//
	int lastFPS = -1;
	int framesPerSecond = -1;
	irr::u32 last = device->getTimer()->getTime();

	while (device->run())
	{
		const irr::u32 now = device->getTimer()->getTime();
		const irr::f32 deltaTime = (irr::f32)(now - last) / 1000.f; // Time in seconds
		last = now;
		if (device->isWindowActive())
		{

			// RunOneIterationOfGameLoop(deltaTime);
		
			// Test Button.
			if (button->isPressed()) {
				rotX += 1; rotY += 1; rotZ += 1;
				meshSceneNode->setRotation(irr::core::vector3df(rotX, rotY, rotZ));
				dirLight->setRotation(irr::core::vector3df(0, rotY, 0));
			}
			
			
			driver->beginScene(true, true, irr::video::SColor(255, 90, 101, 140));
			sceneManager->drawAll();
			guienv->drawAll();
			driver->endScene();

			/*
			// Add FPS to the title.
			framesPerSecond = driver->getFPS();
			if (lastFPS != framesPerSecond)
			{
				irr::core::stringw str = L"Test_Project ";
				str += L"      FPS: ";
				str += framesPerSecond;
				device->setWindowCaption(str.c_str());
				lastFPS = framesPerSecond;
			}
			*/
		}
		else
		{
			device->yield();
		}
	}

	// Remove meshNode from scene.
	meshSceneNode->remove();
	
	device->drop();
	conThread.join();
	delete pLuaEngine;
	
	return EXIT_SUCCESS;
}