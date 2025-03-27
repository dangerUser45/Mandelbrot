Compiler = g++
Target   = Mandelbrot

SRC		 = src/
B		 = build/
H        = headers/

Flags	 = 	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio \
		   	-D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector
#==================================================================================
#----------------------------------------------------------------------------------
#==================================================================================

$(Target): 		$(B)MandelbrotMain.o $(B)MandelbrotCtorDtor.o $(B)MandelbrotDraw.o $(B)MandelbrotLogic.o
	$(Compiler) $(B)MandelbrotMain.o $(B)MandelbrotCtorDtor.o $(B)MandelbrotDraw.o $(B)MandelbrotLogic.o -o $(B)Mandelbrot.out $(Flags)
#----------------------------------------------------------------------------------

$(B)MandelbrotMain.o :		$(SRC)MandelbrotMain.cpp			\
							$(H)MandelbrotConsts.h				\
							$(H)MandelbrotGeneral.h				\
							$(H)MandelbrotCtorDtor.h			\
							$(H)MandelbrotCalc.h				\
							$(H)MandelbrotDraw.h

	$(Compiler) -c $(SRC)MandelbrotMain.cpp -o $(B)MandelbrotMain.o $(Flags)
#----------------------------------------------------------------------------------

$(B)MandelbrotCtorDtor.o: 	$(SRC)MandelbrotCtorDtor.cpp		\
							$(H)MandelbrotCtorDtor.h			\
							$(H)MandelbrotGeneral.h

	$(Compiler) -c $(SRC)MandelbrotCtorDtor.cpp -o $(B)MandelbrotCtorDtor.o $(Flags)
#----------------------------------------------------------------------------------

$(B)MandelbrotDraw.o: 		$(SRC)MandelbrotDraw.cpp			\
							$(H)MandelbrotDraw.h				\
							$(H)MandelbrotGeneral.h

	$(Compiler) -c $(SRC)MandelbrotDraw.cpp -o $(B)MandelbrotDraw.o $(Flags)
#----------------------------------------------------------------------------------

$(B)MandelbrotLogic.o: 		$(SRC)MandelbrotLogic.cpp			\
							$(H)MandelbrotLogic.h				\
							$(H)MandelbrotConsts.h				\
							$(H)MandelbrotGeneral.h

	$(Compiler) -c $(SRC)MandelbrotLogic.cpp -o $(B)MandelbrotLogic.o $(Flags)
#==================================================================================
#----------------------------------------------------------------------------------
#==================================================================================
run:
	$(B)Mandelbrot.out
#----------------------------------------------------------------------------------

clean:
	rm -f $(B)*
#----------------------------------------------------------------------------------
