#define GENERAL_H_INCLUDED

#include <SFML/Graphics.hpp>

struct Mandelbrot
{
    sf::RenderWindow* window;
    sf::VertexArray* pixels;
    sf::Event* event;
};
