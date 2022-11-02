#include "../headers/includes.hpp"

#include "../headers/Parser.hpp"
#include "../headers/Instruction.hpp"
#include "../headers/SIM.hpp"


using namespace std;


int main(int argc, const char * argv[]) {
    
    string input_code_path = "./test.txt";
    
    parser parser(input_code_path);
    SIM sim;
    int fetched_instructions = 0;

    do {
        fetched_instructions = parser.parse();
        sim.add_instructions(parser.get_instructions());
        std::cout << "fetched_instructions count: " << fetched_instructions << std::endl;
        sim.process(fetched_instructions);
    }while (fetched_instructions == INSTRUCTION_MEMORY_SIZE);

    

    return 0;
}
