#ifndef ROUTING
#define ROUTING

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "route.h"
#include "stage_1.h"

struct Route;

class Routing {
  protected:
    SDL_Renderer *renderer;
    SDL_Window *window;
  public:
    static Route* actualRoute;

    explicit Routing (SDL_Renderer *renderer, SDL_Window *window) : renderer(renderer), window(window) {
    }

    static void selectedRoute(RouteEnum routeEnum) {
      for( Route::RouteListClass::iterator routeIterator = Route::routeList.begin();
          routeIterator != Route::routeList.end(); 
          routeIterator ++)
      {
          if ((*routeIterator)->route_id == routeEnum) {
            actualRoute = (*routeIterator);
          }
      }
    }

    void init() {
      Stage1* stage = new Stage1();
    }

    void render() {
      actualRoute->setRenderObj(this->renderer);
      actualRoute->setWindowObj(this->window);
      actualRoute->render();
    }

};

#endif
