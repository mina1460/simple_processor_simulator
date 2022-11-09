#ifndef CORE_HPP
#define CORE_HPP

#include "includes.hpp"
#include "Instruction.hpp"

class Core{
    public:
        Core(int core_id, std::array<std::atomic<int32_t>, DATA_MEMORY_SIZE>* data_memory_pointer);
        void add_instructions(std::vector<Instruction*>& p_instructions);
        void process();
        ~Core();
    private:
        int core_id; // core id
        std::array<Instruction*, INSTRUCTION_MEMORY_SIZE> instructions_memory;  // memory for instructions
        std::array<std::atomic<int32_t>, DATA_MEMORY_SIZE>* data_memory = nullptr;                // pointer to data memory
        int instruction_counter;                        // holds value of current instruction to be executed             
        int data_counter;         
        int32_t instruction_register;   
        int32_t fetched_instructions_count;             
};

#endif /* CORE_HPP */