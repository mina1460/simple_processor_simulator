#include "../headers/includes.hpp"
#include "../headers/SIM.hpp"


SIM::SIM(){
    std::cout << "Constructed SIM" << std::endl;
    instruction_counter = 0;
    data_counter = 0;

}
void SIM::add_instructions(std::vector<Instruction*>& p_instructions){
    instruction_counter = 0;
    for (auto& instruction : p_instructions){
        instructions_memory[instruction_counter] = instruction; //consider here pointers to instructions
        instruction_counter++;
    }
}

void SIM::process(int p_fetched_instructions){
    instruction_counter = 0;
    while (instruction_counter < std::min(p_fetched_instructions, INSTRUCTION_MEMORY_SIZE)){
        instructions_memory[instruction_counter]->execute();
        instruction_counter++;
    }
}

SIM::~SIM(){
    std::cout << "Destructed SIM" << std::endl;
}
