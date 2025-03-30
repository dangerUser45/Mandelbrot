#ifndef CONSTS_INCLUDED
#include <MandelbrotConsts.h>
#endif

#ifndef GENERAL_H_INCLUDED
#include <MandelbrotGeneral.h>
#endif

#include <MandelbrotCtorDtor.h>

#include <Color.h>
#include <SFML/Graphics.hpp>

//--------------------------------------------------------------------------------------------------------------------------
 Mandelbrot* MandelbrotCtorCommon (int argc, char** argv)
{
    int repeat_value = CheckArg (argc, argv);

    Mandelbrot* mandelbrot = new Mandelbrot {0, 0, 0, START_PIXEL_SIZE, X_CENTRE_START_POS, Y_CENTRE_START_POS, 0};

    sf::RenderWindow* window = new sf::RenderWindow (sf::VideoMode(X_WINDOW_SIZE,  Y_WINDOW_SIZE), "Mandelbrot");
    window -> setPosition(sf::Vector2i(CENTRE_RELAT_WINDOW, 0));

    sf::VertexArray* pixels  = new sf::VertexArray  (sf::Points,   X_WINDOW_SIZE * Y_WINDOW_SIZE);

    mandelbrot -> window = window;
    mandelbrot -> pixels = pixels;
    mandelbrot -> repeat_value = repeat_value;

    return mandelbrot;
}
//--------------------------------------------------------------------------------------------------------------------------
int MandelbrotDtorCommon (Mandelbrot* mandelbrot)
{
    delete mandelbrot -> window;
    delete mandelbrot -> pixels;
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
