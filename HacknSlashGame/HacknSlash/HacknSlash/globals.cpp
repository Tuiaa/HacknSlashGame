#include "globals.h"

const float Globals::PI = 3.14159;

bool Globals::debugging = true;

int Globals::ScreenWidth = 640, Globals::ScreenHeight = 352, Globals::ScreenScale = 1;
SDL_Renderer* Globals::renderer = NULL;