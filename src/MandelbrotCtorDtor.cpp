#ifndef GENERAL_H_INCLUDED
#include "../headers/MandelbrotGeneral.h"
#endif

#include "../headers/MandelbrotCtorDtor.h"

#include <SFML/Graphics.hpp>

//--------------------------------------------------------------------------------------------------------------------------
int MandelbrotCtorCommon (Mandelbrot* mandelbrot)
{

    sf::RenderWindow* window = new sf::RenderWindow (sf::VideoMode(900, 600), "Mandelbrot");
    sf::VertexArray* pixels  = new sf::VertexArray  (sf::Points, 900 * 600);

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
