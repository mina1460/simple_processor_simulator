#ifndef SIM_HPP
#define SIM_HPP

#include "includes.hpp"
#include "Core.hpp"
#include "Instruction.hpp"

/* 
    The SIM class is the main class that is responsible for the simulation of the 
    processor. It is responsible for fetching the instructions from the instruction
    memory and executing them. Also, it is responsible for storing the data memory.
*/
class SIM {
    friend class SystemCalls;
    public:
        static int fetched_instructions_count;
        SIM(int n);
        void add_instructions(std::vector<Instruction*>& p_instructions, int core_id);
        void process();
        ~SIM();
    private:
        void execute();
        std::vector<Core> cores;    
        static std::array<std::atomic<int32_t>, DATA_MEMORY_SIZE> data_memory;  // memory for data
        int data_counter;                            
        int32_t instruction_register;   
};

#endif /* SIM_HPP */
