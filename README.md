# MandelbrotExplorer-SDL
An interactive Mandelbrot set explorer, Realtime GPU. 
Powered using SDL and OpenCL.

View square is resized by scroll, and left click and right click is zoom in and zoom out.

![Demonstration](https://s7.gifyu.com/images/mandelbrot145bb7b67b63bd9d.gif)

Running in AMD R7 370 Series 4GB.

# This uses GPU processing?
Yes.
This Kernel is send to CPU.
```
__kernel void MandelbrotPixel(__global float* c, __global float* a)
{
 unsigned int max = 200;
 unsigned int n = get_global_id(0);
 float col = n % (int)(floor(a[4]));
 float row = (int)(n / (int)(floor(a[4])));
 float c_im = 0, c_re = 0;
 float x = 0, y = 0;
 if (a[5] == 0.0) {
 c_im = a[0] - (row * a[2]);
 c_re = a[1] + (col * a[3]);
 }
 if (a[5] == 1.0) {
 x = a[6];
 y = a[7];
 }
 int iteration = 0;
 while (x*x+y*y <= 4 && iteration < max) {
     float x_new = x*x - y*y;
     y = 2*x*y + c_im;
     x = x_new + c_re;
     iteration++;
 }
 if (iteration > max) {
   iteration = 255;
 }
 c[n] = iteration;
}
```



# How compile

With GNU c++ compiler just do.

``` g++ -std=c++11 main.cpp -o mandelbrot -lSDL2_ttf -lSDL2main -lSDL2 -lOpenGL ```

# This tool can be better?
Yes, Basically there is a limitation of the number of decimal places in the float that limits the amount of zoom given in the set, to solve the problem i think of storing information in two variables (which would require a large number of "number tricks" similar to the BigInt and BigFloat libraries )
