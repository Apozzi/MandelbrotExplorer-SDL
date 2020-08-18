# MandelbrotExplorer-SDL
An interactive Mandelbrot set explorer, Realtime GPU. 
Powered using SDL and OpenCL.

View square is resized by scroll, and left click and right click is zoom in and zoom out.

![Demonstration](https://s7.gifyu.com/images/mandelbrot145bb7b67b63bd9d.gif)

# Computing Mandelbrot given X and Y.
![X](https://wikimedia.org/api/rest_v1/media/math/render/svg/b18a3233ed63d7bff11463a0e6683b9a085a14a0)

![Y](https://wikimedia.org/api/rest_v1/media/math/render/svg/94923ff5c86dcb580db28b4146ae1cdcfb93e9c6)


# How compile

With GNU c++ compiler just do.

``` g++ -std=c++11 main.cpp -o mandelbrot -lSDL2_ttf -lSDL2main -lSDL2 -lOpenGL ```
