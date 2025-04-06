#ifndef CONSTS_INCLUDED
#include <MandelbrotConsts.h>
#endif

#ifndef GENERAL_H_INCLUDED
#include <MandelbrotGeneral.h>
#endif

#include <MandelbrotLogic.h>
#include <MandelbrotCalc.h>

#include <SFML/Graphics.hpp>

#ifdef PICTURE_MODE
#include <MandelbrotDraw.h>
#endif

#ifdef STAT_MODE
int counter_time = 0;
#endif

//--------------------------------------------------------------------------------------------------------------------------
int MandelbrotMainLoop (Mandelbrot* mandelbrot)
{
    #ifdef STAT_MODE
    while (counter_time <= NUMBER_DIMENSIONS)
        MandelbrotCalculation (mandelbrot);
    #endif

    #ifdef PICTURE_MODE
    while (mandelbrot -> window -> isOpen())
    {
        MandelbrotLogicCommon (mandelbrot);
        MandelbrotCalculation (mandelbrot);
        DrawSingleIteration   (mandelbrot);
    }
    #endif

    return 0;
}
//--------------------------------------------------------------------------------------------------------------------------
void MandelbrotLogicCommon (Mandelbrot* mandelbrot)
{
    sf::Event event;

    while (mandelbrot -> window -> pollEvent(event))
    {
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wswitch-enum"

        switch (event.type)
        {
            case sf::Event::Closed:
            {
                mandelbrot -> window -> close();
                break;
            }

            #ifndef STAT_MODE
            case sf::Event::KeyPressed:
            {
                if (event.key.scancode == sf::Keyboard::Scan::Escape)
                    mandelbrot -> window -> close();

                else if (event.key.scancode == sf::Keyboard::Scan::Up)
                    mandelbrot -> n_max += 128;

                else if (event.key.scancode == sf::Keyboard::Scan::Down)
                    mandelbrot -> n_max -= 128;

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
            #endif

            default:
                break;
        }
        #pragma GCC diagnostic pop
    }
}
//--------------------------------------------------------------------------------------------------------------------------
FLOAT_TYPE GetCurrentPixelSize(Mandelbrot* mandelbrot, bool zoom)
{
    FLOAT_TYPE new_pixel_size = 0;

    if (zoom)
        new_pixel_size = mandelbrot -> pixel_size / ZOOM_RATE;
    else
        new_pixel_size = mandelbrot -> pixel_size * ZOOM_RATE;

    return new_pixel_size;
}
//--------------------------------------------------------------------------------------------------------------------------
void MoveCenter(Mandelbrot* mandelbrot, FLOAT_TYPE dx_pixels, FLOAT_TYPE dy_pixels)
{
    const FLOAT_TYPE pixel_size = mandelbrot -> pixel_size;

    mandelbrot -> center_x += dx_pixels * pixel_size;
    mandelbrot -> center_y -= dy_pixels * pixel_size;
}
//--------------------------------------------------------------------------------------------------------------------------
