
SRC			= src/
B			= build/

CXX          = g++

CPPSRC 		= $(SRC)MandelbrotMain.cpp $(SRC)MandelbrotCalc.cpp $(SRC)MandelbrotCtorDtor.cpp $(SRC)MandelbrotDraw.cpp $(SRC)MandelbrotLogic.cpp
CPPOBJ 		= $(CPPSRC:$(SRC)%.cpp=$(B)%.o)
CPPDEP     := $(patsubst %.o, %.d, $(CPPOBJ))

CMD	   		= $(B)Mandelbrot.out
#----------------------------------------------------------------------------------

CXXFLAGS_DEBUG	 := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio \
		   		-D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector

CXXFLAGS_RELEASE := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio \
					-O3
#----------------------------------------------------------------------------------

BUILD ?= RELEASE

ifeq ($(BUILD), DEBUG)
	CXXFLAGS = $(CXXFLAGS_DEBUG)

else ifeq ($(BUILD), RELEASE)
	CXXFLAGS = $(CXXFLAGS_RELEASE)

else
    $(error Unknown build type: $(BUILD). Use DEBUG or RELEASE)
endif

override CXXFLAGS += -I./include/
#----------------------------------------------------------------------------------

NO_REPEATS := 1
REPEATS ?= 1

ifeq ($(REPEATS),NO_REPEATS)
	REP_ARG := $(NO_REPEATS)
else
	REP_ARG := $(REPEATS)
endif
#==================================================================================
#----------------------------------------------------------------------------------
#==================================================================================

all:
	$(CXX) $^ -o $(CMD) $(CXXFLAGS)

#----------------------------------------------------------------------------------

$(CPPDEP): $(B)%.d: $(SRC)%.cpp
	mkdir -p $(dir $@)
	$(CC) $< $(CXXFLAGS) -MM -MT '$(B)$*.o $(B)$*.d' -MF $@
include $(CPPDEP)

$(CPPOBJ): $(B)%.o : $(SRC)%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
all: $(CPPOBJ)

#----------------------------------------------------------------------------------

.PHONY: clear
clear:
	rm -rf $(B)*
#----------------------------------------------------------------------------------

# STAT_MODE=0
# PICTURE_MODE=1
#
# if (MODE)

.PHONY: run
run:
	$(CMD) $(REP_ARG)
#----------------------------------------------------------------------------------
