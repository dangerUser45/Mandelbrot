#include <MandelbrotConsts.h>
#include <MandelbrotGeneral.h>
#include <MandelbrotCtorDtor.h>
#include <MandelbrotCalc.h>
#include <MandelbrotLogic.h>
#include <MandelbrotDraw.h>

#include <SFML/Graphics.hpp>

//--------------------------------------------------------------------------------------------------------------------------
int main ()
{
    Mandelbrot mandelbrot = {};
    MandelbrotCtorCommon (&mandelbrot);

    MandelbrotCalculation (mandelbrot.pixels);

    while (mandelbrot.window -> isOpen())
    {
        MandelbrotLogicCommon (&mandelbrot);
        DrawSingleIteration (&mandelbrot);
    }

    MandelbrotDtorCommon (&mandelbrot);
}
//--------------------------------------------------------------------------------------------------------------------------
