#include "../headers/includes.hpp"
#include "../headers/SIM.hpp"

int SIM::fetched_instructions_count = 0;

SIM::SIM(int n){
    std::cout << "Constructed SIM" << std::endl;
    std::cout << "Number of cores: " << n << std::endl;
    for (int i = 0; i < n; i++){
        cores.emplace_back(i, &data_memory);
    }
    std::cout << "Number of cores in the SIM: " << cores.size() << std::endl;
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
    std::cout << "Destructed SIM" << std::endl;
}
