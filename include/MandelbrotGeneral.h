#pragma once

#define GENERAL_H_INCLUDED

#ifndef CONSTS_INCLUDED
#include <MandelbrotConsts.h>
#endif

#include <SFML/Graphics.hpp>

struct Mandelbrot
{
    sf::RenderWindow* window;
    sf::VertexArray* pixels;
    sf::Event* event;

    double pixel_size;   // Базовый размер пикселя (чем меньше - тем больше увеличение)
    double center_x;     // Центр по X
    double center_y;     // Центр по Y

    int repeat_value;
    int n;
};
