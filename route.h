#ifndef ROUTE
#define ROUTE

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <list>
#include <chrono>
#include <thread>
#include <ctime>

using namespace std::chrono;


class Route;
class Routing;

enum class RouteEnum
{
    STAGE1,
    NONE
};


class Route {
  protected:
    int count = 0;
    int actionTime = 0;
    SDL_Renderer *renderer;
    SDL_Window *window;
    int maxFps = 110000;
  public:
    typedef std::list<Route*> RouteListClass;
    static RouteListClass routeList;
    RouteEnum route_id; 
    virtual void init() = 0;
    virtual void script() = 0;

    explicit Route () {
      Route::addRoute(this);
    }

    void render() {
      auto startScript = std::chrono::high_resolution_clock::now();
      this->count++;
      if (this->count == 1) {
        init();
      } else {
        script();
      }
      auto finishScript = std::chrono::high_resolution_clock::now();
      int intervalDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(finishScript-startScript).count();
      int differenceDelay = maxFps - intervalDuration;
      std::cout << " diffMaximumLimit=" << differenceDelay << std::endl; 
      while (differenceDelay > 0) {
        auto startDiff = std::chrono::high_resolution_clock::now();
        auto finishDiff = std::chrono::high_resolution_clock::now();
        int intervalDurationDiff = std::chrono::duration_cast<std::chrono::nanoseconds>(finishDiff-startDiff).count();
        differenceDelay -= intervalDurationDiff;
      }
      auto finishRender = std::chrono::high_resolution_clock::now();
      int intervalDurationRender = std::chrono::duration_cast<std::chrono::nanoseconds>(finishRender-startScript).count();
       std::cout << " nanosecondsProcessing=" << intervalDurationRender << std::endl; 
    }

    void setActionTime(int atime) {
      this->actionTime = atime;
    }

    int getTime() {
      return this->count;
    }

    int getActionTime() {
      return this->actionTime;
    }

    static void addRoute(Route* route) {
      routeList.push_front(route);
    }

    void setRenderObj(SDL_Renderer *renderer) {
      this->renderer = renderer;
    }

    SDL_Renderer* getRenderObj() {
      return this->renderer;
    }

    void setWindowObj(SDL_Window *window) {
      this->window = window;
    }

    SDL_Window* getWindowObj() {
      return this->window;
    }

};

#endif
