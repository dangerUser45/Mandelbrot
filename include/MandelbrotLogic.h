#pragma once

#ifndef GENERAL_H_INCLUDED
#include <MandelbrotGeneral.h>
#endif

void MandelbrotLogicCommon (Mandelbrot* mandelbrot);
double GetCurrentPixelSize(Mandelbrot* mandelbrot, bool zoom);
void MoveCenter(Mandelbrot* mandelbrot, double dx_pixels, double dy_pixels);
