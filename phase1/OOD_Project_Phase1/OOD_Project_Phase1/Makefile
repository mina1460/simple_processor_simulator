CC=g++
C++11=-std=c++17
INCLUDES=-I ./headers
DEBUG=-g
HEADERS=./headers/*.hpp
SOURCE=./source/*.cpp
MASTER=./master/*.cpp
SLAVE=./slave/*.cpp

SIM: $(SOURCE) $(HEADERS)
	$(CC) $(C++11) $(INCLUDES) -o SIM $(SOURCE)

clean:
	rm -f SIM

debug:
	$(CC) $(C++11) $(INCLUDES) $(DEBUG) -o SIM Instruction.cpp main.cpp Parser.cpp SIM.cpp Core.cpp

build_master: $(HEADERS) 
	$(CC) $(C++11) $(INCLUDES) ./master/master.cpp -o master_exe ./source/Parser.cpp ./source/SIM.cpp ./source/Instruction.cpp ./source/Core.cpp ./source/SystemCalls.cpp

build_slave: $(HEADERS)
	$(CC) $(C++11) $(INCLUDES) ./slave/slave.cpp -o slave_exe ./source/Parser.cpp ./source/SIM.cpp ./source/Instruction.cpp ./source/Core.cpp ./source/SystemCalls.cpp