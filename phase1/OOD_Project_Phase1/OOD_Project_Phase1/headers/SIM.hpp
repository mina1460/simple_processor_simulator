#ifndef SIM_HPP
#define SIM_HPP

#include "includes.hpp"
#include "Instruction.hpp"

class SIM {
    public:
        SIM();
        void add_instructions(std::vector<instruction>& p_instructions);
        ~SIM();
    private:
        std::array<instruction, INSTRUCTION_MEMORY_SIZE> instructions_memory;
        std::array<int32_t, DATA_MEMORY_SIZE> data_memory;
        int instruction_counter;
        int data_counter;
        int32_t instruction_register;
    
};

#endif /* SIM_HPP */
