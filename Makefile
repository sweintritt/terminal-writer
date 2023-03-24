GPP=g++
CPP_FLAGS=-std=c++11 \
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

.PHONY: all
all: tw_cpp tw_go

.PHONY: clean
clean:
	rm -f *.o tw_cpp tw_go

tw_cpp: terminal_writer.cpp
	$(GPP) $(CPP_FLAGS) -o $@ $<

tw_go: terminal_writer.go
	go build -o $@ $<