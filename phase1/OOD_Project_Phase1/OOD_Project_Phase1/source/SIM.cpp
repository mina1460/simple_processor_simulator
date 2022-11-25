#include "../headers/includes.hpp"
#include "../headers/SIM.hpp"
#include "../headers/SystemCalls.hpp"

int SIM::fetched_instructions_count = 0;
std::array<std::atomic<int32_t>, DATA_MEMORY_SIZE> SIM::data_memory = {0};

SIM::SIM(int n){
    
    for (int i = 0; i < n; i++){
        cores.emplace_back(i, &data_memory);
    }
    std::cout << "Constructed the SIM with " << cores.size() << " cores " << std::endl;
}

void SIM::add_instructions(std::vector<Instruction*>& p_instructions, int core_id){
    cores[core_id].add_instructions(p_instructions);
}

void SIM::process(){
        // launch threads for each core
        std::vector<std::thread> threads(cores.size());

        for(int id=0; id<cores.size(); id++){
            threads[id] = std::thread(&Core::process, &cores[id]);
        }

        for (auto& thread : threads){
            thread.join();
        }
}

SIM::~SIM(){
    SystemCalls::print_data_memory(25);
    std::cout << "Destructed SIM and its " << cores.size() << " cores " << std::endl;
}
