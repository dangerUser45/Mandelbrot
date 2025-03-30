#pragma once

#ifndef GENERAL_H_INCLUDED
#include <MandelbrotGeneral.h>
#endif

int CheckArg (int argc, char** argv);
Mandelbrot* MandelbrotCtorCommon (int argc, char** argv);
int MandelbrotDtorCommon (Mandelbrot* mandelbrot);
