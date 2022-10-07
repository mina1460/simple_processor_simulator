#ifndef INCLUDES_HPP
#define INCLUDES_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <array>
#include <map>
#include <unordered_map>


#define INSTRUCTION_MEMORY_SIZE 1024
#define DATA_MEMORY_SIZE 1024

typedef short opcode_t;

#define ADD_OPCODE 1
#define NEG_OPCODE 2
#define MUL_OPCODE 3
#define JPA_OPCODE 4
#define JPO_OPCODE 5
#define ASI_OPCODE 6
#define LOE_OPCODE 7
#define HLT_OPCODE 8



#endif /* INCLUDES_HPP */
