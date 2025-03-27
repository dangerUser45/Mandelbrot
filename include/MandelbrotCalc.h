#ifndef CONSTS_INCLUDED
#include <MandelbrotConsts.h>
#endif

#include <SFML/Graphics.hpp>

//--------------------------------------------------------------------------------------------------------------------------
inline void MandelbrotCalculation (sf::VertexArray* pixels)
{
    for (size_t y_pos = 0; y_pos < 600; ++y_pos, y0 -= dy)
    {
        x0 = -2.0;

        for (size_t x_pos = 0; x_pos < 900; ++x_pos, x0 += dx)
        {
            double x = x0;
            double y = y0;

            int n = 0;
            for (; n < nmax; ++n)
            {
                double x2 = x * x;
                double y2 = y * y;
                double xy = x * y;

                double r2 = x2 + y2;

                if (r2 >= r2max) break;

                x = x2 - y2 + x0;
                y = xy + xy + y0;
            }

            (*pixels)[y_pos * 900 + x_pos].position = sf::Vector2f((float)x_pos, (float)y_pos);
            (*pixels)[y_pos * 900 + x_pos].color    = sf::Color((n * 16) % 256, (n * 8) % 256, (n * 4) % 256);
        }
    }
}
//--------------------------------------------------------------------------------------------------------------------------
