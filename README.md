# MandelbrotExplorer-SDL
An interactive Mandelbrot set explorer, Realtime GPU. 
Powered using SDL and OpenCL.

View square is resized by scroll, and left click and right click is zoom in and zoom out.

![Demonstration](https://s7.gifyu.com/images/mandelbrot145bb7b67b63bd9d.gif)

# How compile

With GNU c++ compiler just do.

``` g++ -std=c++11 main.cpp -o mandelbrot -lSDL2_ttf -lSDL2main -lSDL2 -lOpenGL ```
