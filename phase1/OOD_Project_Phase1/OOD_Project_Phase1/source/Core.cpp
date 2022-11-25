#include "Core.hpp"
#include "includes.hpp"
#include "Instruction.hpp"

Core::Core(int core_id, std::array<std::atomic<int32_t>, DATA_MEMORY_SIZE>* data_memory_pointer){
    std::cout << "Constructed Core " << core_id << std::endl;
    data_memory = data_memory_pointer;
    this->core_id = core_id;
}

void Core::add_instructions(std::vector<Instruction*>& p_instructions){
    instruction_counter = 0;
    for (auto& instruction : p_instructions){
        // set the instruction counter and data counter inside the instruction object
        instruction->set_data_memory(data_memory);
        instruction->set_instruction_counter(&instruction_counter);
        instructions_memory[instruction_counter] = instruction; //consider here pointers to instructions
        instruction_counter++;
    }
    fetched_instructions_count = p_instructions.size();
    std::cout << "Added " << fetched_instructions_count << " instructions to Core " << core_id << std::endl;
}

void Core::process(){
    try{
        std::stringstream ss;
        ss << "Core " << core_id << " started processing in the thread " << std::endl;
        std::cout << ss.str();
        // while the instruction counter is less than the number of instructions and INSTRUCTION_MEMORY_SIZE
        instruction_counter = 0;
        while (instruction_counter < std::min(Core::fetched_instructions_count, INSTRUCTION_MEMORY_SIZE)){
            // get the instruction from the instruction memory
            instructions_memory[instruction_counter]->set_fetched_instructions_count(&fetched_instructions_count);
            // execute the instruction
            instructions_memory[instruction_counter]->set_core_id(core_id);
            instructions_memory[instruction_counter]->execute();
            if (instructions_memory[instruction_counter]->get_opcode() == HLT_OPCODE){
                std::stringstream log_msg;
                log_msg << "***** Core " << core_id << " HALTING *****" << std::endl;
                std::cout << log_msg.str();
                return;
            }
            // increment the instruction counter
            instruction_counter++;
        }
    } catch (const std::exception& e){
        std::cout << "Error executing instruction: " << e.what() << std::endl;
        throw e;
    }
}


Core::~Core(){
}