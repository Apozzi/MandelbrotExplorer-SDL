#ifndef MATH_LINE
#define MATH_LINE

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "math_point.h"

// (Y - Y1) / (Y2 - Y1) = (X - X1) / (X2 - X1)
// ax + b

class Line {
  protected:
    double x1, x2, y1, y2, a, b;

    void defineLineFunction() {
      int tempDiv = (x1 - x2);
      this->a = (y1 - y2) / tempDiv;
      this->b = (x1*y2 - x2*y1) / tempDiv;
    }
  public:
    Line(double x1, double x2, double y1, double y2) : x1(x1), x2(x2), y1(y1), y2(y2) {
      this->defineLineFunction();
    }

    Line(Point* p1, Point* p2) {
      x1 = p1->getX();
      x2 = p2->getX();
      y1 = p1->getY();
      y2 = p2->getY();
      this->defineLineFunction();
    }

    Point* getPercentagePoint(double perc) {
      double xp = x1 + ((x2 - x1) * perc);
      double yp = y1 + ((y2 - y1) * perc);
      return new Point(xp, yp);
    }

    bool hasInterception(Line* object) {
      double dif = (this->a - object->a);
      double xIncog;
      double yIncog;
      if (dif != 0) {
        xIncog = (object->b - this->b) / dif;
        yIncog = (this->a * xIncog) + this->b;
        std::cout << "xIncog:" << xIncog << "|yIncog" << yIncog << std::endl;
      } else {
        return object->b == this->b;
      }
      return this->isPointOnLine(xIncog, yIncog) && object->isPointOnLine(xIncog, yIncog);
    }

    bool isPointOnLine(double x, double y) {
      bool onLineThisX = (this->x1 >= x && this->x2 <= x) || (this->x2 >= x && this->x1 <= x);
      bool onLineThisY = (this->y1 >= y && this->y2 <= y) || (this->y2 >= y && this->y1 <= y);
      bool isInLine = y == (this->a * x) + this->b;
      return onLineThisX && onLineThisY && isInLine;
    }

};

#endif
