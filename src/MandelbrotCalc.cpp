#ifndef CONSTS_INCLUDED
#include <MandelbrotConsts.h>
#endif

#ifndef GENERAL_H_INCLUDED
#include <MandelbrotGeneral.h>
#endif

#ifdef INTRINSICS_ALG
#include <immintrin.h>
#endif

#ifdef INTRINSICS_FAST_ALG
#include <immintrin.h>
#endif

#include <MandelbrotCalc.h>
#include <Color.h>

#include <SFML/Graphics.hpp>
#include <time.h>

#include <cmath>

#ifdef STAT_MODE
#include <MandelbrotLogic.h>

extern int counter_time;
#endif

//--------------------------------------------------------------------------------------------------------------------------
#ifdef SIMPLE_ALG
void MandelbrotCalculation (Mandelbrot* mandelbrot)
{
    #ifdef PICTURE_MODE
    sf::Uint8* pixels = mandelbrot -> pixels;
    #endif

    const FLOAT_TYPE pixel_size = mandelbrot -> pixel_size;
    const FLOAT_TYPE center_x   = mandelbrot -> center_x;
    const FLOAT_TYPE center_y   = mandelbrot -> center_y;

    const FLOAT_TYPE width  = X_WINDOW_SIZE * pixel_size;
    const FLOAT_TYPE height = Y_WINDOW_SIZE * pixel_size;

    // Начальные координаты (левый верхний угол)
    FLOAT_TYPE x0 = center_x - width  / 2;
    FLOAT_TYPE y0 = center_y + height / 2;

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
                FLOAT_TYPE x = x0;
                FLOAT_TYPE y = y0;

                n = 0;
                for (; n < nmax; ++n)
                {
                    FLOAT_TYPE x2 = x * x;
                    FLOAT_TYPE y2 = y * y;
                    FLOAT_TYPE xy = x * y;

                    FLOAT_TYPE r2 = x2 + y2;

                    if (r2 >= r2max) break;

                    x = x2 - y2 + x0;
                    y = xy + xy + y0;
                }
            }

            #ifdef PICTURE_MODE
            int index = (y_pos*X_WINDOW_SIZE + x_pos) * 4;

            pixels[index    ] = (n * 22) % 256;  //R
            pixels[index + 1] = (n * 14) % 256;  //G
            pixels[index + 2] = (n * 17) % 256;  //B
            pixels[index + 3] = 255;             //A
            #endif

            mandelbrot -> n = n;

        }
    }


    clock_gettime(CLOCK_MONOTONIC, &end);
    long double duration_ms = (end.tv_sec - start.tv_sec) * ONE_THOUSAND + (end.tv_nsec - start.tv_nsec) / ONE_MILLION;

    #ifndef STAT_MODE
    printf("" RED "Time: %.1Lf ms" RESET "\r", duration_ms);
    fflush(stdout);
    PrintAverage(ONE_THOUSAND / duration_ms, "\t\t" CYAN "FPS: %.1Lf" RESET "\r");
    #endif

    #ifdef STAT_MODE
    MeasureTimeData (mandelbrot, duration_ms);
    fflush(stdout);
    #endif

    #ifdef PICTURE_MODE
    mandelbrot -> texture -> update (pixels);
    #endif
}
#endif

//--------------------------------------------------------------------------------------------------------------------------
#ifdef NATIVE_ALG
void MandelbrotCalculation (Mandelbrot* mandelbrot)
{
    #ifdef PICTURE_MODE
    sf::Uint8* pixels = mandelbrot -> pixels;
    #endif

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

        for (int x_pos = 0; x_pos < X_WINDOW_SIZE; x_pos += NATIVE_LOOP_NUMBER, x0 += pixel_size*NATIVE_LOOP_NUMBER)
        {
            int N[NATIVE_LOOP_NUMBER] = {};
            for (int i = 0; i < repeat_value; i++)
            {
                FLOAT_TYPE X0[NATIVE_LOOP_NUMBER] = {}; for (int i = 0; i < NATIVE_LOOP_NUMBER; ++i) {X0[i] = x0 + i*pixel_size;}

                FLOAT_TYPE Y0[NATIVE_LOOP_NUMBER] = {}; for (int i = 0; i < NATIVE_LOOP_NUMBER; ++i) {Y0[i] = y0;}

                FLOAT_TYPE X[NATIVE_LOOP_NUMBER]  = {}; for (int i = 0; i < NATIVE_LOOP_NUMBER; i++) {X[i] = X0[i];}
                FLOAT_TYPE Y[NATIVE_LOOP_NUMBER]  = {}; for (int i = 0; i < NATIVE_LOOP_NUMBER; i++) {Y[i] = Y0[i];}

                for (int n = 0; n < nmax; ++n)
                {
                    FLOAT_TYPE X2[NATIVE_LOOP_NUMBER] = {}; for (int i = 0; i < NATIVE_LOOP_NUMBER; i++) { X2[i] = X[i] * X[i];}
                    FLOAT_TYPE Y2[NATIVE_LOOP_NUMBER] = {}; for (int i = 0; i < NATIVE_LOOP_NUMBER; i++) { Y2[i] = Y[i] * Y[i];}
                    FLOAT_TYPE XY[NATIVE_LOOP_NUMBER] = {}; for (int i = 0; i < NATIVE_LOOP_NUMBER; i++) { XY[i] = X[i] * Y[i];}

                    FLOAT_TYPE R2[NATIVE_LOOP_NUMBER] = {}; for (int i = 0; i < NATIVE_LOOP_NUMBER; i++) { R2[i] = X2[i] + Y2[i];}

                    int cmp[NATIVE_LOOP_NUMBER] = {};
                    for (int i = 0; i < NATIVE_LOOP_NUMBER; i++) { if (R2[i] <= r2max) cmp[i] = 1;}

                    int mask = 0;
                    for (int i = 0; i < NATIVE_LOOP_NUMBER; i++) { mask |= (cmp[i] << i);}
                    if (!mask) break;

                    for (int i = 0; i < NATIVE_LOOP_NUMBER; i++) {N[i] = N[i] + cmp[i];}

                    for (int i = 0; i < NATIVE_LOOP_NUMBER; i++) { X[i] = X2[i] - Y2[i] + X0[i];}
                    for (int i = 0; i < NATIVE_LOOP_NUMBER; i++) { Y[i] = XY[i] + XY[i] + Y0[i];}
                }
            }

            #ifndef STAT_MODE
            int index = (y_pos*X_WINDOW_SIZE + x_pos) * 4;    // * 4 because RGBA - 4 bytes
            for (int i = 0; i < NATIVE_LOOP_NUMBER; i++)
            {
                pixels[index + 4*i    ] = (N[i] * 22) % 256;  //R
                pixels[index + 4*i + 1] = (N[i] * 14) % 256;  //G
                pixels[index + 4*i + 2] = (N[i] * 17) % 256;  //B
                pixels[index + 4*i + 3] = 255;                //A
            }
            #endif

            mandelbrot -> n = N[0];
        }
    }


    clock_gettime(CLOCK_MONOTONIC, &end);
    long double duration_ms = (end.tv_sec - start.tv_sec) * ONE_THOUSAND + (end.tv_nsec - start.tv_nsec) / ONE_MILLION;

    #ifdef PICTURE_MODE
    printf("" RED "Time: %.1Lf ms" RESET "\r", duration_ms);
    fflush(stdout);
    PrintAverage(ONE_THOUSAND / duration_ms, "\t\t" CYAN "FPS: %.1Lf" RESET "\r");
    #endif

    #ifdef STAT_MODE
    MeasureTimeData (mandelbrot, duration_ms);
    fflush(stdout);
    #endif

    #ifdef PICTURE_MODE
    mandelbrot -> texture -> update (pixels);
    #endif
}
#endif

//--------------------------------------------------------------------------------------------------------------------------
#ifdef INTRINSICS_ALG
void MandelbrotCalculation (Mandelbrot* mandelbrot)
{
    #ifdef PICTURE_MODE
    sf::Uint8* pixels = mandelbrot -> pixels;
    #endif

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

        for (int x_pos = 0; x_pos < X_WINDOW_SIZE; x_pos += 8, x0 += pixel_size*8)
        {
            __m256i N = _mm256_setzero_si256();
            for (int i = 0; i < repeat_value; i++)
            {
                __m256 X0 = _mm256_setr_ps(x0, x0 + pixel_size, x0 + pixel_size*2, x0 + pixel_size*3,
                                           x0 + pixel_size*4, x0 + pixel_size*5, x0 + pixel_size*6, x0 + pixel_size*7);

                __m256 Y0 = _mm256_set1_ps(y0);

                __m256 X = X0;
                __m256 Y = Y0;

                for (int n = 0; n < nmax; ++n)
                {
                    __m256 X2 = _mm256_mul_ps(X, X);
                    __m256 Y2 = _mm256_mul_ps(Y, Y);
                    __m256 XY = _mm256_mul_ps(X, Y);

                    __m256 R2 = _mm256_add_ps(X2, Y2);
                    __m256 mask = _mm256_cmp_ps(R2, _mm256_set1_ps(r2max), _CMP_LE_OQ);

                    if (_mm256_testz_ps(mask, mask)) break;

                    __m256i mask_i = _mm256_castps_si256(mask);
                    mask_i = _mm256_and_si256(mask_i, _mm256_set1_epi32(1));

                    N = _mm256_add_epi32(N, mask_i);

                    X = _mm256_add_ps(_mm256_sub_ps(X2, Y2), X0);
                    Y = _mm256_add_ps(_mm256_add_ps(XY, XY), Y0);
                }
            }

            alignas(32) int counts[8];
            _mm256_store_si256((__m256i*)counts, N);

            #ifndef STAT_MODE
            for (int i = 0; i < 8; i++)
            {
                int index = (y_pos * X_WINDOW_SIZE + x_pos + i) * 4;

                pixels[index    ] = (counts[i] * 22) % 256;
                pixels[index + 1] = (counts[i] * 14) % 256;
                pixels[index + 2] = (counts[i] * 17) % 256;
                pixels[index + 3] = 255;
            }
            #endif

            mandelbrot-> n = counts[7]; // Чтобы компилятор не стирал всю функцию
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    long double duration_ms = (end.tv_sec - start.tv_sec) * ONE_THOUSAND + (end.tv_nsec - start.tv_nsec) / ONE_MILLION;

    #ifdef PICTURE_MODE
    printf("" RED "Time: %.1Lf ms" RESET "\r", duration_ms);
    fflush(stdout);
    PrintAverage(ONE_THOUSAND / duration_ms, "\t\t" CYAN "FPS: %.1Lf" RESET "\r");
    #endif

    #ifdef STAT_MODE
    MeasureTimeData (mandelbrot, duration_ms);
    fflush(stdout);
    #endif

    #ifdef PICTURE_MODE
    mandelbrot -> texture -> update (pixels);
    #endif
}
#endif

//--------------------------------------------------------------------------------------------------------------------------
#ifdef INTRINSICS_FAST_ALG
void MandelbrotCalculation(Mandelbrot* mandelbrot)
{
    #ifdef PICTURE_MODE
    sf::Uint8* pixels = mandelbrot -> pixels;
    #endif

    const FLOAT_TYPE pixel_size = mandelbrot->pixel_size;
    const FLOAT_TYPE center_x = mandelbrot->center_x;
    const FLOAT_TYPE center_y = mandelbrot->center_y;

    const FLOAT_TYPE width = X_WINDOW_SIZE * pixel_size;
    const FLOAT_TYPE height = Y_WINDOW_SIZE * pixel_size;

    FLOAT_TYPE x0 = center_x - width / 2;
    FLOAT_TYPE y0 = center_y + height / 2;

    const int repeat_value = mandelbrot->repeat_value;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int y_pos = 0; y_pos < Y_WINDOW_SIZE; ++y_pos, y0 -= pixel_size)
    {
        x0 = center_x - width / 2;

        for (int x_pos = 0; x_pos < X_WINDOW_SIZE; x_pos += 8*INTRIN_LOOP_NUMBER, x0 += pixel_size*8*INTRIN_LOOP_NUMBER)
        {
            __m256i N[INTRIN_LOOP_NUMBER] = {};

            for (int i = 0; i < repeat_value; i++)
            {
                __m256 X0[INTRIN_LOOP_NUMBER];
                __m256 Y0[INTRIN_LOOP_NUMBER];
                __m256  X[INTRIN_LOOP_NUMBER];
                __m256  Y[INTRIN_LOOP_NUMBER];

                // Инициализация начальных значений
                for (int block = 0; block < INTRIN_LOOP_NUMBER; block++)
                {
                    X0[block] = _mm256_setr_ps
                    (
                        x0 + pixel_size*(block*8 + 0),
                        x0 + pixel_size*(block*8 + 1),
                        x0 + pixel_size*(block*8 + 2),
                        x0 + pixel_size*(block*8 + 3),
                        x0 + pixel_size*(block*8 + 4),
                        x0 + pixel_size*(block*8 + 5),
                        x0 + pixel_size*(block*8 + 6),
                        x0 + pixel_size*(block*8 + 7)
                    );
                    Y0[block] = _mm256_set1_ps(y0);
                    X[block] = X0[block];
                    Y[block] = Y0[block];
                }

                for (int n = 0; n < mandelbrot -> n_max; ++n)
                {
                    int all_zero = 1;

                    for (int block = 0; block < INTRIN_LOOP_NUMBER; block++)
                    {
                        __m256 X2 = _mm256_mul_ps(X[block], X[block]);
                        __m256 Y2 = _mm256_mul_ps(Y[block], Y[block]);
                        __m256 XY = _mm256_mul_ps(X[block], Y[block]);
                        __m256 R2 = _mm256_add_ps(X2, Y2);

                        __m256 mask = _mm256_cmp_ps(R2, _mm256_set1_ps(r2max), _CMP_LE_OQ);
                        int mask_result = _mm256_movemask_ps(mask);

                        if (mask_result != 0)
                        {
                            all_zero = 0;
                            __m256i mask_i = _mm256_castps_si256(mask);
                            mask_i = _mm256_and_si256(mask_i, _mm256_set1_epi32(1));
                            N[block] = _mm256_add_epi32(N[block], mask_i);
                        }

                        X[block] = _mm256_add_ps(_mm256_sub_ps(X2, Y2), X0[block]);
                        Y[block] = _mm256_add_ps(_mm256_add_ps(XY, XY), Y0[block]);
                    }

                    if (all_zero) break;
                }
            }

            alignas(32) int counts[INTRIN_LOOP_NUMBER][8];
            for (int block = 0; block < INTRIN_LOOP_NUMBER; block++)
            {
                _mm256_store_si256((__m256i*)counts[block], N[block]);

                #ifndef STAT_MODE
                for (int j = 0; j < 8; j++)
                {
                    int index = (y_pos * X_WINDOW_SIZE + x_pos + block*8 + j) * 4;

                    if (index + 3 < X_WINDOW_SIZE * Y_WINDOW_SIZE * 4)
                    {
                        pixels[index]     = (counts[block][j] * 22) % 256;
                        pixels[index + 1] = (counts[block][j] * 14) % 256;
                        pixels[index + 2] = (counts[block][j] * 17) % 256;
                        pixels[index + 3] = 255;
                    }
                }
                #endif
            }

            mandelbrot -> n = counts[1][1];
        }
    }


    clock_gettime(CLOCK_MONOTONIC, &end);
    long double duration_ms = (end.tv_sec - start.tv_sec) * ONE_THOUSAND + (end.tv_nsec - start.tv_nsec) / ONE_MILLION;

    #ifdef PICTURE_MODE
    printf("" RED "Time: %.1Lf ms" RESET "\r", duration_ms);
    fflush(stdout);
    PrintAverage(ONE_THOUSAND / duration_ms, "\t\t" CYAN "FPS: %.1Lf" RESET "\r");
    #endif

    #ifdef STAT_MODE
    MeasureTimeData (mandelbrot, duration_ms);
    fflush(stdout);
    #endif

    #ifdef PICTURE_MODE
    mandelbrot -> texture -> update (pixels);
    #endif
}
#endif

//--------------------------------------------------------------------------------------------------------------------------
void PrintAverage (long double single_value, const char* format_string)
{
    static int counter = 0;
    static long double values [NUMBER_COUNTS_AVERAGE] = {};

    if (counter == NUMBER_COUNTS_AVERAGE)
    {
        for (int i = 1; i < NUMBER_COUNTS_AVERAGE; ++i)
        {
            values [0] += values[i];
            counter = 0;
        }

        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wformat-nonliteral"

        printf (format_string, values[0] / NUMBER_COUNTS_AVERAGE);

        #pragma GCC diagnostic pop

        fflush(stdout);
        return;
    }

    values[counter] = single_value;
    ++counter;
    printf ("\r");

    return;
}
//--------------------------------------------------------------------------------------------------------------------------
#ifdef STAT_MODE
void MeasureTimeData (Mandelbrot* mandelbrot, long double duration_ms)
{
    long double* time_array = mandelbrot -> time_array;

    if (counter_time == NUMBER_DIMENSIONS)
    {
        for (int i = 0; i < NUMBER_COUNTS_AVERAGE; ++i)
        {
            time_array[NUMBER_DIMENSIONS] += time_array[i];
            ++counter_time;
            //counter_time   = 0;
        }

        time_array[NUMBER_DIMENSIONS] /= NUMBER_COUNTS_AVERAGE;
        AccuracyCalculation (mandelbrot);
        fflush(stdout);

        return;

    }
    time_array[counter_time] = duration_ms;
    printf ("%2d. Current time = %Lf milliseconds\n", counter_time + 1, time_array[counter_time]);
    ++counter_time;
}
//--------------------------------------------------------------------------------------------------------------------------
long double AccuracyCalculation (Mandelbrot* mandelbrot)
{
    long double* time_array = mandelbrot -> time_array;
    long double sigma_time  = 0;
    long double average_time = time_array[NUMBER_DIMENSIONS];

    for (int i = 0; i < NUMBER_DIMENSIONS; ++i)
        sigma_time += (time_array[i] - average_time) * (time_array[i] - average_time);

    sigma_time = sqrtl(sigma_time / (NUMBER_DIMENSIONS * (NUMBER_DIMENSIONS - 1)));

    printf ("\n" MAGENTA ";-----------------------------------------------------;"
            "\n"         ";                                                     ;"
            "\n"         "; Measured value:   " RESET YELLOW "(%.2lf +- %.2lf ) milliseconds    " MAGENTA ";"
            "\n"         ";                                                     ;"
            "\n"         ";-----------------------------------------------------;\n" RESET, round(average_time * 10) / 10, round(sigma_time * 10) / 10);

    return sigma_time;
}

#endif
//--------------------------------------------------------------------------------------------------------------------------
