#include "../headers/includes.hpp"

#include "../headers/Parser.hpp"
#include "../headers/Instruction.hpp"
#include "../headers/SIM.hpp"


using namespace std;


int main(int argc, const char * argv[]) {
    
    // Check if the user provided a file name
    if (argc != 2){
        cout << "Usage: ./SIM <input_file_path>" << endl;
        return 1;
    }
    // store the file name
    string input_code_path = argv[1];
    
    // Create a parser object and parse the input file
    parser parser(input_code_path);

    // Create a SIM object and run the simulation
    SIM sim;

    int fetched_instructions = 0;

    try{
        // Fetch the instructions
        fetched_instructions = parser.parse();
        // add the instructions to the SIM
        sim.add_instructions(parser.get_instructions());
        // get the fetched instructions count
        SIM::fetched_instructions_count = fetched_instructions;
        // report the fetched instructions count
        std::cout << "fetched_instructions count: " << SIM::fetched_instructions_count << std::endl;

        // run the simulation
        sim.process();
    }catch (const std::exception& e){
        return EXIT_FAILURE;
    }

    return 0;
}
