#include <SFML/Graphics/Texture.hpp>
#ifndef CONSTS_INCLUDED
#include <MandelbrotConsts.h>
#endif

#ifndef GENERAL_H_INCLUDED
#include <MandelbrotGeneral.h>
#endif

#include <MandelbrotCtorDtor.h>

#include <Color.h>
#include <SFML/Graphics.hpp>

#ifdef STAT_MODE
#include <MandelbrotDraw.h>
#endif

//--------------------------------------------------------------------------------------------------------------------------
 Mandelbrot* MandelbrotCtorCommon (int argc, char** argv)
{
    int repeat_value = CheckArg (argc, argv);

    Mandelbrot* mandelbrot = new Mandelbrot {0, 0, 0, 0, 0, 0, 0, 0, START_PIXEL_SIZE, X_CENTRE_START_POS, Y_CENTRE_START_POS, 0, 0};

    #ifdef STAT_MODE
    timespec* start_all_time = new timespec;
    timespec*   end_all_time = new timespec;

    clock_gettime(CLOCK_MONOTONIC, start_all_time);

    mandelbrot -> start_all_time = start_all_time;
    mandelbrot ->   end_all_time =   end_all_time;
    #endif

    #ifdef PICTURE_MODE
    sf::RenderWindow* window = new sf::RenderWindow (sf::VideoMode(X_WINDOW_SIZE,  Y_WINDOW_SIZE), "Mandelbrot");
    window -> setPosition(sf::Vector2i(CENTRE_RELAT_WINDOW, 0));

    sf::Uint8*   pixels  = new sf::Uint8[X_WINDOW_SIZE * Y_WINDOW_SIZE * 4]; // * 4 because pixels have 4 components (RGBA)
    sf::Texture* texture = new sf::Texture;

    texture -> create (X_WINDOW_SIZE, Y_WINDOW_SIZE);

    sf::Sprite* sprite  = new sf::Sprite(*texture);
    sprite -> setTexture(*texture);

    mandelbrot -> window  = window;

    mandelbrot -> sprite  = sprite;
    mandelbrot -> texture = texture;
    mandelbrot -> pixels  = pixels;
    #endif

    mandelbrot -> time_array = new long double[NUMBER_DIMENSIONS + 1]();

    mandelbrot -> repeat_value = repeat_value;
    mandelbrot -> n_max = nmax;

    return mandelbrot;
}
//--------------------------------------------------------------------------------------------------------------------------
int MandelbrotDtorCommon (Mandelbrot* mandelbrot)
{
    delete mandelbrot -> window;

    delete mandelbrot -> sprite;
    delete mandelbrot -> texture;
    delete mandelbrot -> pixels;

    delete[] mandelbrot -> time_array;

    #ifdef STAT_MODE
    PrintAllTime (mandelbrot -> start_all_time, mandelbrot -> end_all_time);
    delete   mandelbrot -> start_all_time;
    delete   mandelbrot ->   end_all_time;
    #endif

    delete mandelbrot;

    return 0;
}
//--------------------------------------------------------------------------------------------------------------------------
int CheckArg (int argc, char** argv)
{
    if (argc != NUMBER_ARGS)
    {
        printf ("%s: %d: *" RED "ERROR: Uncorrect number of arguments" RESET "*\n", __FILE__, __LINE__);
        exit (1);
    }

    for (int i = 0; argv[1][i] != ' '; i++)
    {
        if (!(isdigit (argv[1][0])))
        {
            printf ("%s: %d: *" RED "ERROR: Uncorrect repeat value" RESET "*\n", __FILE__, __LINE__);
            exit (2);
        }
    }

    int repeat_value = atoi (argv[1]);

    return repeat_value;
}
//--------------------------------------------------------------------------------------------------------------------------
