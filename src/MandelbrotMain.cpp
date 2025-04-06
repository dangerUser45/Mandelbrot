#include <MandelbrotGeneral.h>
#include <MandelbrotCtorDtor.h>
#include <MandelbrotLogic.h>

//--------------------------------------------------------------------------------------------------------------------------
int main (int argc, char** argv)
{
    Mandelbrot* mandelbrot = MandelbrotCtorCommon (argc, argv);
    MandelbrotMainLoop (mandelbrot);
    MandelbrotDtorCommon (mandelbrot);
}
//--------------------------------------------------------------------------------------------------------------------------
