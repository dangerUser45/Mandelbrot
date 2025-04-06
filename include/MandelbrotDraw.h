#pragma once

#include <SFML/Graphics.hpp>

#ifndef GENERAL_H_INCLUDED
#include <MandelbrotGeneral.h>
#endif

void DrawSingleIteration (Mandelbrot* mandelbrot);
void PrintAllTime (timespec* start, timespec* end);
