#include "cleanup.h"
#include "res_path.h"
#include "drawing_functions.h"
#include "SDL_mixer.h"

// A bit hacky way to resolve issue with SDL2 and Visual Studio 2015
#ifdef main
#undef main
#endif

int main(int argc, char **agv) {

	// Setup SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "Error initialising SDL" << endl;
		return 1;
	}

	// Setup window
	SDL_Window *window = SDL_CreateWindow("HacknSlash", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		640, 352, SDL_WINDOW_SHOWN); // Fullscreen --> SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN

	if (window == nullptr) {
		SDL_Quit();
		cout << "Error initialising window" << endl;
		return 1;
	}

	// Setup renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		cleanup(window);
		SDL_Quit();
		cout << "Renderer error" << endl;
		return 1;
	}

	// The size to draw things at, before we scale it to the screen size dimensions mentioned in CreateWindow
	SDL_RenderSetLogicalSize(renderer, 640, 352);

	// Initialise SDL_Image
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		SDL_Quit();
		cout << "SDL Image did not initialise" << endl;
		return 1;
	}

	// Initialise text to font
	if (TTF_Init() != 0) {
		SDL_Quit();
		cout << "SDL_TTF did not initialise" << endl;
		return 1;
	}

	// Initialise SDL Mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		SDL_Quit();
		cout << "Mixer did not initialise" << endl;
		return 1;
	}

	// Load up a texture to draw
	string resourcePath = getResourcePath();
	SDL_Texture *texture = loadTexture(resourcePath + "map.png", renderer);
	
	// Run game for 5000 ticks
	while (SDL_GetTicks() < 5000) {
		// Clear the screen
		SDL_RenderClear(renderer);
		// Draw what we want to the screen
		renderTexture(texture, renderer, 0, 0);
		// Show image we've been rendering
		SDL_RenderPresent(renderer);
	}

	cleanup(renderer);
	cleanup(window);
	cleanup(texture);

	SDL_Quit();
	return 0;
}