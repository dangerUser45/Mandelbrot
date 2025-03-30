#include <MandelbrotConsts.h>
#include <MandelbrotGeneral.h>
#include <MandelbrotCtorDtor.h>
#include <MandelbrotCalc.h>
#include <MandelbrotLogic.h>
#include <MandelbrotDraw.h>

#include <SFML/Graphics.hpp>
#include <Color.h>

//--------------------------------------------------------------------------------------------------------------------------
int main (int argc, char** argv)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    Mandelbrot* mandelbrot = MandelbrotCtorCommon (argc, argv);

    while (mandelbrot -> window -> isOpen())
    {
        MandelbrotLogicCommon (mandelbrot);
        MandelbrotCalculation (mandelbrot);
        DrawSingleIteration   (mandelbrot);
    }

    MandelbrotDtorCommon (mandelbrot);

    clock_gettime(CLOCK_MONOTONIC, &end);
    long double duration_ms = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / ONE_BILLION;  //time in seconds
    printf("\nall time: %Lf seconds\r\n", duration_ms);
    fflush(stdout);
}
//--------------------------------------------------------------------------------------------------------------------------
