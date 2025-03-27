#ifndef GENERAL_H_INCLUDED
#include <MandelbrotGeneral.h>
#endif

#include <MandelbrotLogic.h>

#include <SFML/Graphics.hpp>

//--------------------------------------------------------------------------------------------------------------------------
void MandelbrotLogicCommon (Mandelbrot* mandelbrot)
{
    sf::Event event;
    while (mandelbrot -> window -> pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            mandelbrot -> window -> close();
    }
}
//--------------------------------------------------------------------------------------------------------------------------
