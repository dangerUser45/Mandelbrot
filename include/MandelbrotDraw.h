#include <SFML/Graphics.hpp>

#ifndef GENERAL_H_INCLUDED
#include <MandelbrotGeneral.h>
#endif

//--------------------------------------------------------------------------------------------------------------------------
inline void DrawSingleIteration (Mandelbrot* mandelbrot)
{
    mandelbrot -> window -> clear ();
    mandelbrot -> window -> draw (*(mandelbrot -> pixels));
    mandelbrot -> window -> display ();
}
//--------------------------------------------------------------------------------------------------------------------------

