CC=g++
C++11=-std=c++17
INCLUDES=-I ./headers
DEBUG=-g
HEADERS=./headers/*.hpp
SOURCE=./source/*.cpp

SIM: $(SOURCE) $(HEADERS)
	$(CC) $(C++11) $(INCLUDES) -o SIM $(SOURCE)

clean:
	rm -f SIM

debug:
	$(CC) $(C++11) $(INCLUDES) $(DEBUG) -o SIM Instruction.cpp main.cpp Parser.cpp SIM.cpp Core.cpp