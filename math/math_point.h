#ifndef MATH_POINT
#define MATH_POINT

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

class Point {
  protected:
    
    double x, y;
  public:
    Point(double x, double y) : x(x), y(y) {
    }
    void setX(double setx) {
      x = setx;
    }
    void setY(double sety) {
      y = sety;
    }
    double getX() {
      return x;
    }
    double getY() {
      return y;
    }
    Point* clone() {
      return new Point(x, y);
    }
    Point* addX(int xadd) {
      x += xadd;
      return this;
    }
    Point* addY(int yadd) {
      y += yadd;
      return this;
    }
    Point* add(Point* p) {
      x += p->getX();
      y += p->getY();
      return this;
    }

};

#endif
