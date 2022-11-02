#ifndef SIM_HPP
#define SIM_HPP

#include "includes.hpp"
#include "Instruction.hpp"

class SIM {
    public:
        static int fetched_instructions_count;
        SIM();
        void add_instructions(std::vector<Instruction*>& p_instructions);
        void process();
        ~SIM();
    private:
        void execute();
        std::array<Instruction*, INSTRUCTION_MEMORY_SIZE> instructions_memory;
        std::array<int32_t, DATA_MEMORY_SIZE> data_memory = {0};
        int instruction_counter;
        int data_counter;
        int32_t instruction_register;
};

#endif /* SIM_HPP */
