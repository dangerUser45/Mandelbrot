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

            case sf::Event::MouseWheelScrolled:
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                    std::cout << "wheel type: vertical" << std::endl;
                else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
                    std::cout << "wheel type: horizontal" << std::endl;
                else
                std::cout << "wheel type: unknown" << std::endl;
                std::cout << "wheel movement: " << event.mouseWheelScroll.delta << std::endl;
                std::cout << "mouse x: " << event.mouseWheelScroll.x << std::endl;
                std::cout << "mouse y: " << event.mouseWheelScroll.y << std::endl;
                break;
            }

            case sf::Event::KeyPressed:
            {
                if (event.key.scancode == sf::Keyboard::Scan::Escape)
                    mandelbrot -> window -> close();

                else if (event.key.scancode == sf::Keyboard::Scan::W)
                    MoveCenter (mandelbrot, 0, -10);

                else if (event.key.scancode == sf::Keyboard::Scan::A)
                    MoveCenter (mandelbrot, -10, 0);

                else if (event.key.scancode == sf::Keyboard::Scan::S)
                    MoveCenter (mandelbrot, 0, +10);

                else if (event.key.scancode == sf::Keyboard::Scan::D)
                    MoveCenter (mandelbrot, +10, 0);

                else if (event.key.control)
                {
                    if (event.key.scancode == sf::Keyboard::Scan::Num1)
                        /* load data to file */ break;

                    else if (event.key.scancode == sf::Keyboard::Scan::Equal)
                    {
                        HandleZoom (mandelbrot, true);
                        mandelbrot -> pixel_size = GetCurrentPixelSize (mandelbrot);
                    }

                    else if (event.key.scancode == sf::Keyboard::Scan::Hyphen)
                    {
                        mandelbrot -> pixel_size = GetCurrentPixelSize (mandelbrot);
                        HandleZoom (mandelbrot, false);
                    }
                }
            }

            default:
                break;
        }
    }
}
//--------------------------------------------------------------------------------------------------------------------------
double GetCurrentPixelSize(Mandelbrot* mandelbrot)
{
    return mandelbrot -> pixel_size / (1.0 + mandelbrot -> zoom_level * 0.1);
}
//--------------------------------------------------------------------------------------------------------------------------
void HandleZoom(Mandelbrot* mandelbrot, bool zoomIn)
{
    if (zoomIn)
        mandelbrot -> zoom_level += zoomStep;

    else
    {
        if (mandelbrot -> zoom_level > -7.0)
            mandelbrot -> zoom_level -= zoomStep;

    }
    std::cout << "Current zoom level = " << mandelbrot -> zoom_level <<std::endl;
}
//--------------------------------------------------------------------------------------------------------------------------
void MoveCenter(Mandelbrot* mandelbrot, double dx_pixels, double dy_pixels)
{
    const double pixel_size = GetCurrentPixelSize(mandelbrot);

    mandelbrot -> center_x += dx_pixels * pixel_size;
    mandelbrot -> center_y -= dy_pixels * pixel_size;
}
//--------------------------------------------------------------------------------------------------------------------------
