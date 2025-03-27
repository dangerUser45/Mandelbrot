#include "../headers/MandelbrotConsts.h"
#include "../headers/MandelbrotGeneral.h"
#include "../headers/MandelbrotCtorDtor.h"
#include "../headers/MandelbrotCalc.h"
#include "../headers/MandelbrotDraw.h"

#include <SFML/Graphics.hpp>

//--------------------------------------------------------------------------------------------------------------------------
int main ()
{
    Mandelbrot mandelbrot = {};
    CtorCommon (&mandelbrot);

    MandelbrotCalculation (mandelbrot.pixels);

    while (mandelbrot.window -> isOpen())
    {
        sf::Event event;
        while (mandelbrot.window -> pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mandelbrot.window -> close();
        }

        DrawSingleIteration (&mandelbrot);
    }

    return 0;
}
//--------------------------------------------------------------------------------------------------------------------------
