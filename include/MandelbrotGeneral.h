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

    double pixel_size = START_PIXEL_SIZE;  // Базовый размер пикселя (чем меньше - тем больше увеличение)
    double zoom_level = 0.0;    // Текущий уровень зума (0 = 100%)
    double center_x   = -0.5;   // Центр по X
    double center_y   = 0.0;    // Центр по Y
};
