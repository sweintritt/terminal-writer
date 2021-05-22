.PHONY: all clean check run

APP=tw
SRC=terminal_writer.cpp
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

all: clean $(APP)

clean:
	rm -f *.o $(APP)

check:
	cppcheck . \
	--suppress=missingIncludeSystem \
	--std=$(STD) \
	--report-progress \
	--enable=all \
	--language=c++ \
	--inconclusive \
	--platform=unix64

$(APP): $(SRC)
	$(GCC) $(FLAGS) -o $@ $< $(LIBS)
