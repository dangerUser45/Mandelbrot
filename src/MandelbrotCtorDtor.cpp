#ifndef CONSTS_INCLUDED
#include <MandelbrotConsts.h>
#endif

#ifndef GENERAL_H_INCLUDED
#include <MandelbrotGeneral.h>
#endif

#include <MandelbrotCtorDtor.h>

#include <SFML/Graphics.hpp>

//--------------------------------------------------------------------------------------------------------------------------
int MandelbrotCtorCommon (Mandelbrot* mandelbrot)
{

    sf::RenderWindow* window = new sf::RenderWindow (sf::VideoMode(X_WINDOW_SIZE,  Y_WINDOW_SIZE), "Mandelbrot");
    window -> setPosition(sf::Vector2i(CENTRE_RELAT_WINDOW, 0));

    sf::VertexArray* pixels  = new sf::VertexArray  (sf::Points,   X_WINDOW_SIZE * Y_WINDOW_SIZE);

    mandelbrot -> window = window;
    mandelbrot -> pixels = pixels;

    return 0;
}
//--------------------------------------------------------------------------------------------------------------------------
int MandelbrotDtorCommon (Mandelbrot* mandelbrot)
{
    delete mandelbrot -> window;
    delete mandelbrot -> pixels;

    return 0;
}
//--------------------------------------------------------------------------------------------------------------------------
