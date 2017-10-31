#ifndef GLOBALS
#define GLOBALS

#include <string>
#include <iostream>
#include <SDL.h>
#include "randomNumber.h"

class Globals {
public:
	// Math helpers
	static const float PI;

	// Useful for me as a dev
	static bool debugging;

	// SDL related
	static int ScreenWidth, ScreenHeight, ScreenScale;
	static SDL_Renderer *renderer;
};

#endif