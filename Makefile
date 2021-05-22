.PHONY: all clean check run

GCC=g++
STD=c++11
FLAGS=-std=$(STD) \
	  -O3 \
	  -Wall \
	  -Werror \
	  -Wextra \
	  -Wpedantic \
	  -Wundef \
	  -Wunused \
	  -Wshadow \
	  -Weffc++ \
	  -Wunreachable-code \
	  -Wfatal-errors \
	  -Wfloat-equal \
	  -ftrapv

all: clean screenwriter

clean:
	rm -f *.o screenwriter

check:
	cppcheck . \
	--suppress=missingIncludeSystem \
	--std=$(STD) \
	--report-progress \
	--enable=all \
	--language=c++ \
	--inconclusive \
	--platform=unix64

%: %.cpp
	$(GCC) $(FLAGS) -o $@ $< $(LIBS)

%.o: %.cpp
	$(GCC) $(FLAGS) -c $< $(LIBS)
