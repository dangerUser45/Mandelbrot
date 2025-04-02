#pragma once

#define GENERAL_H_INCLUDED

#ifndef CONSTS_INCLUDED
#include <MandelbrotConsts.h>
#endif

#include <SFML/Graphics.hpp>

struct Mandelbrot
{
    sf::RenderWindow* window;

    sf::Sprite* sprite;
    sf::Texture* texture;
    sf::Uint8* pixels;

    sf::Event* event;

    FLOAT_TYPE pixel_size;   // Базовый размер пикселя (чем меньше - тем больше увеличение)
    FLOAT_TYPE center_x;     // Центр по X
    FLOAT_TYPE center_y;     // Центр по Y

    int repeat_value;
    int n_max;
    int n;
};
