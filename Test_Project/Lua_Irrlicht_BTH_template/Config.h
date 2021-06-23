#pragma once
#include <dimension2d.h>
#include <EDriverTypes.h>
#include <irrString.h>
#include <irrTypes.h>
#include <Keycodes.h>

struct engine_config_t
{
	irr::core::stringw title = "Default";
	bool fullscreen = false;
	bool vSync = false;
	int	antiAlias = 0;
	int window_width = 1920;
	int window_height = 1080;
};

struct window_config_t
{

};

struct game_config_t
{

};

struct video_config_t
{

};

struct controls_config_t
{
	irr::EKEY_CODE Up = irr::KEY_KEY_W;
	irr::EKEY_CODE Down = irr::KEY_KEY_A;
	irr::EKEY_CODE Left = irr::KEY_KEY_D;
	irr::EKEY_CODE Right = irr::KEY_KEY_S;
	irr::EKEY_CODE Fire = irr::KEY_MBUTTON;
};
