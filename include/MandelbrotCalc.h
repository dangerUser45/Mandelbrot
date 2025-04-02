#pragma once

#ifndef GENERAL_H_INCLUDED
#include <MandelbrotGeneral.h>
#endif

#include <SFML/Graphics.hpp>

void MandelbrotCalculation(Mandelbrot* mandelbrot);
void PrintAverage (long double single_value, const char* format_string);
