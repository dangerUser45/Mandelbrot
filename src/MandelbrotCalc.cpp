#ifndef CONSTS_INCLUDED
#include <MandelbrotConsts.h>
#endif

#ifndef GENERAL_H_INCLUDED
#include <MandelbrotGeneral.h>
#endif

#include <MandelbrotCalc.h>

#include <SFML/Graphics.hpp>
#include <time.h>

//--------------------------------------------------------------------------------------------------------------------------
void MandelbrotCalculation (Mandelbrot* mandelbrot)
{
    const double pixel_size = mandelbrot -> pixel_size;
    const double center_x   = mandelbrot -> center_x;
    const double center_y   = mandelbrot -> center_y;

    const double width  = X_WINDOW_SIZE * pixel_size;
    const double height = Y_WINDOW_SIZE * pixel_size;

    // Начальные координаты (левый верхний угол)
    double x0 = center_x - width  / 2;
    double y0 = center_y + height / 2;

    const int repeat_value = mandelbrot -> repeat_value;

    int n = 0;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (size_t y_pos = 0; y_pos < Y_WINDOW_SIZE; ++y_pos, y0 -= pixel_size)
    {
        x0 = center_x - width / 2;

        for (size_t x_pos = 0; x_pos < X_WINDOW_SIZE; ++x_pos, x0 += pixel_size)
        {
            for (int i = 0; i < repeat_value; i++)
            {
                double x = x0;
                double y = y0;

                n = 0;
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
            }

            #ifndef STAT_MODE
            (*(mandelbrot -> pixels))[y_pos * X_WINDOW_SIZE + x_pos].position = sf::Vector2f((float)x_pos, (float)y_pos);
            (*(mandelbrot -> pixels))[y_pos * X_WINDOW_SIZE + x_pos].color    = sf::Color((n * 22) % 256, (n * 14) % 256, (n * 17) % 256);
            #endif
            mandelbrot -> n = n;

        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    long double duration_ms = (end.tv_sec - start.tv_sec) * ONE_THOUSAND + (end.tv_nsec - start.tv_nsec) / ONE_MILLION;  //time in milliseconds
    printf("test time: %Lf milliseconds\r", duration_ms);
    fflush(stdout);
}
