SRC			= src/
B			= build/

CXX          = g++
CXXFLAGS	 = 	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio \
		   		-D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector

override CXXFLAGS += -I./include/

CPPSRC 		= $(SRC)MandelbrotCtorDtor.cpp $(SRC)MandelbrotDraw.cpp $(SRC)MandelbrotLogic.cpp $(SRC)MandelbrotMain.cpp

CPPOBJ 		= $(B)MandelbrotCtorDtor.o $(B)MandelbrotDraw.o $(B)MandelbrotLogic.o $(B)MandelbrotMain.o
CMD	   		= $(B)Mandelbrot.out
#==================================================================================
#----------------------------------------------------------------------------------
#==================================================================================

all: $(CPPOBJ)
	@mkdir -p $(B)
	$(CXX) $^ -o $(CMD) $(CXXFLAGS)
#----------------------------------------------------------------------------------

$(CPPOBJ): $(B)%.o : $(SRC)%.cpp
	@mkdir -p $(B)
	$(CXX) $(CXXFLAGS) -MP -MMD -c $< -o $@
#----------------------------------------------------------------------------------

.PHONY: clear
clear:
	rm -rf $(B)*
#----------------------------------------------------------------------------------

.PHONY: run
run:
	$(CMD)
#----------------------------------------------------------------------------------
