#ifndef GENERAL_H_INCLUDED
#include <MandelbrotGeneral.h>
#endif

#include <MandelbrotDraw.h>

#include <SFML/Graphics.hpp>

//--------------------------------------------------------------------------------------------------------------------------
void DrawSingleIteration (Mandelbrot* mandelbrot)
{
    #ifndef STAT_MODE
    mandelbrot -> window -> clear ();
    mandelbrot -> window -> draw (*(mandelbrot -> sprite));
    mandelbrot -> window -> display ();
    #endif
}
//--------------------------------------------------------------------------------------------------------------------------
