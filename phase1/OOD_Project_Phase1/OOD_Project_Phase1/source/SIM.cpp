#include "../headers/includes.hpp"
#include "../headers/SIM.hpp"

int SIM::fetched_instructions_count = 0;

SIM::SIM(){
    std::cout << "Constructed SIM" << std::endl;
    instruction_counter = 0;
    data_counter = 0;

}
void SIM::add_instructions(std::vector<Instruction*>& p_instructions){
    instruction_counter = 0;
    for (auto& instruction : p_instructions){
        instruction->set_data_memory(&data_memory);
        instruction->set_instruction_counter(&instruction_counter);
        instructions_memory[instruction_counter] = instruction; //consider here pointers to instructions
        instruction_counter++;
    }
}

void SIM::process(){
    try{
        instruction_counter = 0;
        while (instruction_counter < std::min(SIM::fetched_instructions_count, INSTRUCTION_MEMORY_SIZE)){
            instructions_memory[instruction_counter]->set_fetched_instructions_count(&SIM::fetched_instructions_count);
            instructions_memory[instruction_counter]->execute();
            instruction_counter++;
        }
    } catch (const std::exception& e){
        std::cout << "Error executing instruction: " << e.what() << std::endl;
        throw e;
    }
}

SIM::~SIM(){
    std::cout << "Destructed SIM" << std::endl;

    // for (int i = 0; i < 20; i++){
    //     std::cout << "data_memory[" << i << "]: " << data_memory[i] << std::endl;
    // }
}
