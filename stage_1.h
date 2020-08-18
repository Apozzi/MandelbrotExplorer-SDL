#ifndef STAGE_1
#define STAGE_1

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "route.h"
#include "math/math_point.h"
#include "utils/draw_shape.h"
#include "utils/pixel_map.h"
#include "IO/IO_keys.h"
#include "IO/IO_cursor.h"

#include <CL/cl.h>

const char* OpenCLSource[] = {
"__kernel void MandelbrotPixel(__global float* c, __global float* a)",
"{",
" unsigned int max = 200;",
" unsigned int n = get_global_id(0);",
" float col = n % (int)(floor(a[4]));",
" float row = (int)(n / (int)(floor(a[4])));",
" float c_im = 0, c_re = 0;",+
" float x = 0, y = 0;",
" if (a[5] == 0.0) {",
" c_im = a[0] - (row * a[2]);",
" c_re = a[1] + (col * a[3]);",
" }",
" if (a[5] == 1.0) {",
" x = a[6];",
" y = a[7];",
" }",
" int iteration = 0;",
" while (x*x+y*y <= 4 && iteration < max) {",
"     float x_new = x*x - y*y;",
"     y = 2*x*y + c_im;",
"     x = x_new + c_re;",
"     iteration++;",
" }",
" if (iteration > max) {",
"   iteration = 255;",
" }",
" c[n] = iteration;",
"}"
};


class Stage1  : public Route  {
  protected:
    DrawShape* drawShape;
    PixelMap* pixelMap;
    cl_device_id cdDevice;
    cl_context GPUContext;
    cl_program OpenCLProgram;
    cl_kernel MandelbrotPixel;
    Point* pFocus;
    int height = 680;
    int width = 840;
    double MinRe;
    double MaxRe;
    double MinIm;
    double MaxIm;
    int jb = 0;
    int jr = 0;
    int ji = 0;
  public:
    Stage1() : Route() {
      this->route_id = RouteEnum::STAGE1;
    }

    void init() {
      std::cout << "render route" << std::endl; 
      drawShape = new DrawShape(this->renderer);
      pixelMap = new PixelMap(width, height);
      pixelMap->init(this->renderer);
      MinRe = -2;
      MaxRe = 1;
      MinIm = -1.1;
      MaxIm = MinIm + (MaxRe - MinRe) * height / width;
      cl_platform_id cpPlatform;
      clGetPlatformIDs(1, &cpPlatform, NULL);
      cdDevice;
      clGetDeviceIDs(cpPlatform, CL_DEVICE_TYPE_GPU, 1, &cdDevice, NULL);
      GPUContext = clCreateContextFromType(0, CL_DEVICE_TYPE_GPU, NULL, NULL, NULL);
      OpenCLProgram = clCreateProgramWithSource(GPUContext, 28, OpenCLSource, NULL, NULL);
      clBuildProgram(OpenCLProgram, 0, NULL, NULL, NULL, NULL);
    }

    void script() {
      double Re_factor = (MaxRe - MinRe) / (width - 1);
      double Im_factor = (MaxIm - MinIm) / (height - 1);
      if (IoKeys::isKeyPressed(97)) {
        MinRe+= Re_factor*10;
        MaxRe+= Re_factor*10;
      } else {
        if (IoKeys::isKeyPressed(100)) {
        MinRe-= Re_factor*10;
        MaxRe-= Re_factor*10;
        }
      }
      if (IoKeys::isKeyPressed(119)) {
        MinIm-= Im_factor*10;
        MaxIm-= Im_factor*10;
      } else {
        if (IoKeys::isKeyPressed(115)) {
          MinIm+= Im_factor*10;
          MaxIm+= Im_factor*10;
        }
      }
      
      int SIZE = height*width;
      float HostVector1[SIZE];
      float HostOutputVector[SIZE];
      float InitialData1[8] = {MaxIm,MinRe,Im_factor,Re_factor,width,jb,jr,ji};
      for(int c = 0; c < SIZE; c++)
      {
            HostVector1[c] = InitialData1[c%8];
            HostOutputVector[c] = 0;
      }
      char cBuffer[1024];
      cl_command_queue cqCommandQueue = clCreateCommandQueue(GPUContext, cdDevice, 0, NULL);
      MandelbrotPixel = clCreateKernel(OpenCLProgram, "MandelbrotPixel", NULL);
      cl_mem GPUVector1 = clCreateBuffer(GPUContext, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float) * SIZE, HostVector1, NULL);
      cl_mem GPUOutputVector = clCreateBuffer(GPUContext, CL_MEM_WRITE_ONLY, sizeof(float) * SIZE, NULL, NULL);
      clSetKernelArg(MandelbrotPixel, 0, sizeof(cl_mem), (void*)&GPUOutputVector);
      clSetKernelArg(MandelbrotPixel, 1, sizeof(cl_mem), (void*)&GPUVector1);
      size_t WorkSize[1] = {SIZE};
      clEnqueueNDRangeKernel(cqCommandQueue, MandelbrotPixel, 1, NULL,
      WorkSize, NULL, 0, NULL, NULL);
      clEnqueueReadBuffer(cqCommandQueue, GPUOutputVector, CL_TRUE, 0,
      SIZE * sizeof(float), HostOutputVector, 0, NULL, NULL);
      clReleaseCommandQueue(cqCommandQueue);
      clReleaseMemObject(GPUVector1);
      clReleaseMemObject(GPUOutputVector);
      for(int c = 0; c < SIZE; c++)
      {
        pixelMap->putPixel(c % width,c / width, HostOutputVector[c], HostOutputVector[c], HostOutputVector[c]);
      }
      pixelMap->render(this->renderer);
      int xRect = width/10 + IoCursor::getScroll()*(width/110);
      int yRect = height/10 + IoCursor::getScroll()*(height/110);
      pFocus = new Point(IoCursor::getX() - xRect/2, IoCursor::getY() - yRect/2);
      drawShape->drawRectangle(pFocus, xRect ,yRect);
      if (IoCursor::clicked()) {
        MinRe += pFocus->getX() * Re_factor;
        MaxRe -= (width - pFocus->getX() - xRect) * Re_factor;
        MaxIm -= pFocus->getY() * Im_factor;
        MinIm += (height - pFocus->getY() - yRect) * Im_factor;
      }

      if (IoKeys::isKeyPressed(32)) {
        if (jb == 0) {
          jb = 1;
        } else {           
          jb = 0;
        }
        jr = IoCursor::getX() * Re_factor;
        ji = IoCursor::getX() * Im_factor;
      }
    }

    ~Stage1() {
      clReleaseKernel(MandelbrotPixel);
      clReleaseContext(GPUContext);
      clReleaseProgram(OpenCLProgram);
      delete pixelMap;
      delete drawShape;
      
    }

};

#endif
