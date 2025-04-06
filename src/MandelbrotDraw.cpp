#ifndef GENERAL_H_INCLUDED
#include <MandelbrotGeneral.h>
#endif

#include <MandelbrotDraw.h>

#include <SFML/Graphics.hpp>
#include <time.h>
#include <Color.h>

//--------------------------------------------------------------------------------------------------------------------------
void DrawSingleIteration (Mandelbrot* mandelbrot)
{
    mandelbrot -> window -> clear ();
    mandelbrot -> window -> draw (*(mandelbrot -> sprite));
    mandelbrot -> window -> display ();
}
//--------------------------------------------------------------------------------------------------------------------------
void PrintAllTime (timespec* start, timespec* end)
{
#ifdef STAT_MODE
    clock_gettime(CLOCK_MONOTONIC, end);
    long double duration_ms = (end -> tv_sec - start -> tv_sec) + (end -> tv_nsec - start ->tv_nsec) / ONE_BILLION;  //time in seconds

    printf("\nall time: %.1Lf seconds\r\n%s--------------------------------------------------------------------------------%s\n", duration_ms, BLUE, RESET);
    fflush(stdout);
#endif
}
//--------------------------------------------------------------------------------------------------------------------------
