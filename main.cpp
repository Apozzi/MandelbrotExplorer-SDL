#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "math/math_line.h"
#include "utils/error_logger.h"
#include "IO/IO_keys.h"
#include "IO/IO_cursor.h"
#include "route.h"
#include "routing.h"


/*----------------- THIS CODE IS PROPERTY OF A.POZZI ------------------
            Go to stage_1.h for mandelbrot implementation
----------------------------------------------------------------------- */

const int SCREEN_WIDTH  = 840;
const int SCREEN_HEIGHT = 680;

std::set<int> IoKeys::keys = {};
Point* IoCursor::position;
Point* IoCursor::lastClickPosition;
int IoCursor::state;
int IoCursor::previousState;
int IoCursor::scroll;
std::list<Route*> Route::routeList = {};
Route* Routing::actualRoute = {};

int main(int, char**){
//----------------- Inicializacao ------------------
if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
	logSDLError(std::cout, "SDL_Init");
	return 1;
}

if (TTF_Init() != 0){
	logSDLError(std::cout, "TTF_Init");
	SDL_Quit();
	return 1;
}

//----------------- Criado a janela ------------------
SDL_Window *window = SDL_CreateWindow("Init", 100, 100, SCREEN_WIDTH,
	SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
if (window == nullptr){
	logSDLError(std::cout, "CreateWindow");
	SDL_Quit();
	return 1;
}

//----------------- Renderizador ------------------
SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
if (renderer == nullptr){
	logSDLError(std::cout, "CreateRenderer");
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 1;
}

//----------------  Game Loop ----------------------
SDL_Event e;
bool quit = false;
IoKeys* ioKeysController = new IoKeys();
IoCursor * ioCursorController = new IoCursor();
Routing* routing = new Routing(renderer, window);
routing->init();
routing->selectedRoute(RouteEnum::STAGE1);
while (!quit){
	while (SDL_PollEvent(&e)){
		if (e.type == SDL_QUIT){
			quit = true;
		}
		ioKeysController->defineKeyStateByEvent(e);
		ioCursorController->defineCursorStateByEvent(e);
	}
	SDL_RenderClear(renderer);
	routing->render();
	SDL_RenderPresent(renderer);
}

SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();


SDL_Quit();

delete ioKeysController;
delete ioCursorController;
delete routing;
return 0;
}
