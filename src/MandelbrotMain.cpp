#include "../headers/MandelbrotConsts.h"
#include "../headers/MandelbrotGeneral.h"
#include "../headers/MandelbrotCtorDtor.h"
#include "../headers/MandelbrotCalc.h"
#include "../headers/MandelbrotLogic.h"
#include "../headers/MandelbrotDraw.h"

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
