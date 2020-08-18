#ifndef DRAW_SHAPE
#define DRAW_SHAPE

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <math.h>
#include "../math/math_point.h"
#include "../math/math_line.h"


class DrawShape {
  protected:
    SDL_Renderer *renderer;

  public:
    DrawShape(SDL_Renderer *renderer) : renderer(renderer) {
    }

    void drawLine(Point* p1, Point* p2) {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
      SDL_RenderDrawLine(this->renderer, p1->getX(), p1->getY(), p2->getX(), p2->getY());
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    }


    void drawRectangle(Point *pi, int top, int left) {
        Point* p1 = pi->clone()->addX(top);
        Point* p2 = pi->clone()->addX(top)->addY(left);
        Point* p3 = pi->clone()->addY(left);
        this->drawLine(pi, p1);
        this->drawLine(p1, p2);
        this->drawLine(p2, p3);
        this->drawLine(p3, pi);
        for (auto &p : {p1, p2, p3}) { delete p; }
    }

};

#endif
