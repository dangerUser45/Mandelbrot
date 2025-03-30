#ifndef CONSTS_INCLUDED
#include <MandelbrotConsts.h>
#endif

#ifndef GENERAL_H_INCLUDED
#include <MandelbrotGeneral.h>
#endif

#include <MandelbrotLogic.h>

#include <SFML/Graphics.hpp>
#include <iostream>

//--------------------------------------------------------------------------------------------------------------------------
void MandelbrotLogicCommon (Mandelbrot* mandelbrot)
{
    sf::Event event;

    while (mandelbrot -> window -> pollEvent(event))
    {

        switch (event.type)
        {
            case sf::Event::Closed:
            {
                mandelbrot -> window -> close();
                break;
            }

            case sf::Event::KeyPressed:
            {
                if (event.key.scancode == sf::Keyboard::Scan::Escape)
                    mandelbrot -> window -> close();

                else if (event.key.scancode == sf::Keyboard::Scan::W)
                    MoveCenter (mandelbrot, 0, -PIXEL_SHIFT);

                else if (event.key.scancode == sf::Keyboard::Scan::A)
                    MoveCenter (mandelbrot, -PIXEL_SHIFT, 0);

                else if (event.key.scancode == sf::Keyboard::Scan::S)
                    MoveCenter (mandelbrot, 0, +PIXEL_SHIFT);

                else if (event.key.scancode == sf::Keyboard::Scan::D)
                    MoveCenter (mandelbrot, +PIXEL_SHIFT, 0);

                else if (event.key.control)
                {
                    if (event.key.scancode == sf::Keyboard::Scan::Num1)
                        /* load data to file */ break;

                    else if (event.key.scancode == sf::Keyboard::Scan::Equal)
                        mandelbrot -> pixel_size = GetCurrentPixelSize (mandelbrot, true);


                    else if (event.key.scancode == sf::Keyboard::Scan::Hyphen)
                        mandelbrot -> pixel_size = GetCurrentPixelSize (mandelbrot, false);
                }
            }

            default:
                break;
        }
    }
}
//--------------------------------------------------------------------------------------------------------------------------
double GetCurrentPixelSize(Mandelbrot* mandelbrot, bool zoom)
{
    double new_pixel_size = 0;

    if (zoom)
        new_pixel_size = mandelbrot -> pixel_size / ZOOM_RATE;
    else
        new_pixel_size = mandelbrot -> pixel_size * ZOOM_RATE;

    return new_pixel_size;
}
//--------------------------------------------------------------------------------------------------------------------------
void MoveCenter(Mandelbrot* mandelbrot, double dx_pixels, double dy_pixels)
{
    const double pixel_size = mandelbrot -> pixel_size;

    mandelbrot -> center_x += dx_pixels * pixel_size;
    mandelbrot -> center_y -= dy_pixels * pixel_size;
}
//--------------------------------------------------------------------------------------------------------------------------
