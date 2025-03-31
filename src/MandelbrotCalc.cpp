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
    sf::Uint8* pixels = mandelbrot -> pixels;
    const FLOAT_TYPE pixel_size = mandelbrot -> pixel_size;
    const FLOAT_TYPE center_x   = mandelbrot -> center_x;
    const FLOAT_TYPE center_y   = mandelbrot -> center_y;

    const FLOAT_TYPE width  = X_WINDOW_SIZE * pixel_size;
    const FLOAT_TYPE height = Y_WINDOW_SIZE * pixel_size;

    // Начальные координаты (левый верхний угол)
    FLOAT_TYPE x0 = center_x - width  / 2;
    FLOAT_TYPE y0 = center_y + height / 2;

    const int repeat_value = mandelbrot -> repeat_value;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int y_pos = 0; y_pos < Y_WINDOW_SIZE; ++y_pos, y0 -= pixel_size)
    {
        x0 = center_x - width / 2;

        for (int x_pos = 0; x_pos < X_WINDOW_SIZE; x_pos += 4, x0 += pixel_size*4)
        {
            int N[4] = {0, 0, 0, 0};
            for (int i = 0; i < repeat_value; i++)
            {
                FLOAT_TYPE X0[4] = {x0, x0 + pixel_size, x0 + pixel_size*2, x0 + pixel_size*3};
                FLOAT_TYPE Y0[4] = {y0, y0,              y0,                y0};

                FLOAT_TYPE X[4]  = {}; for (int i = 0; i < 4; i++) {X[i] = X0[i];}
                FLOAT_TYPE Y[4]  = {}; for (int i = 0; i < 4; i++) {Y[i] = Y0[i];}

                for (int n = 0; n < nmax; ++n)
                {
                    FLOAT_TYPE X2[4] = {}; for (int i = 0; i < 4; i++) { X2[i] = X[i] * X[i];}
                    FLOAT_TYPE Y2[4] = {}; for (int i = 0; i < 4; i++) { Y2[i] = Y[i] * Y[i];}
                    FLOAT_TYPE XY[4] = {}; for (int i = 0; i < 4; i++) { XY[i] = X[i] * Y[i];}

                    FLOAT_TYPE R2[4] = {}; for (int i = 0; i < 4; i++) { R2[i] = X2[i] + Y2[i];}

                    int cmp[4] = {0, 0, 0, 0};
                    for (int i = 0; i < 4; i++) { if (R2[i] <= r2max) cmp[i] = 1;}

                    int mask = 0;
                    for (int i = 0; i < 4; i++) { mask |= (cmp[i] << i);}
                    if (!mask) break;

                    for (int i = 0; i < 4; i++) {N[i] = N[i] + cmp[i];}

                    for (int i = 0; i < 4; i++) { X[i] = X2[i] - Y2[i] + X0[i];}
                    for (int i = 0; i < 4; i++) { Y[i] = XY[i] + XY[i] + Y0[i];}
                }
            }

            #ifndef STAT_MODE
            int index = (y_pos*X_WINDOW_SIZE + x_pos) * 4;
            for (int i = 0; i < 4; i++)
            {
                pixels[index + 4*i    ] = (N[i] * 22) % 256;  //R
                pixels[index + 4*i + 1] = (N[i] * 14) % 256;  //G
                pixels[index + 4*i + 2] = (N[i] * 17) % 256;  //B
                pixels[index + 4*i + 3] = 255;                //A
            }
            #endif

            //mandelbrot -> n = N[0] + N[1] + N[2] + N[3];
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    FLOAT_TYPE duration_ms = (end.tv_sec - start.tv_sec) * ONE_THOUSAND + (end.tv_nsec - start.tv_nsec) / ONE_MILLION;  //time in milliseconds
    printf("test time: %lf milliseconds\r", duration_ms);
    fflush(stdout);

    mandelbrot -> texture -> update (pixels);
}
