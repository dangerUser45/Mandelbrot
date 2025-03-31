#pragma once

#ifndef GENERAL_H_INCLUDED
#include <MandelbrotGeneral.h>
#endif

void MandelbrotLogicCommon (Mandelbrot* mandelbrot);
FLOAT_TYPE GetCurrentPixelSize (Mandelbrot* mandelbrot, bool zoom);
void MoveCenter(Mandelbrot* mandelbrot, FLOAT_TYPE dx_pixels, FLOAT_TYPE dy_pixels);
