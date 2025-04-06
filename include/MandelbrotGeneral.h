#pragma once

#define GENERAL_H_INCLUDED

#ifndef CONSTS_INCLUDED
#include <MandelbrotConsts.h>
#endif

#include <SFML/Graphics.hpp>

struct Mandelbrot
{
    long double* time_array;
    timespec* start_all_time;
    timespec*   end_all_time;

    sf::RenderWindow* window;

    sf::Sprite*  sprite;
    sf::Texture* texture;
    sf::Uint8*   pixels;

    sf::Event*   event;

    FLOAT_TYPE pixel_size;   // Начальный размер пикселя (сколько математических у.е. приходится на один пиксель) (чем меньше - тем больше увеличение)
    FLOAT_TYPE center_x;     // Центр по X
    FLOAT_TYPE center_y;     // Центр по Y

    int repeat_value;
    int n_max;
    int n;
};
