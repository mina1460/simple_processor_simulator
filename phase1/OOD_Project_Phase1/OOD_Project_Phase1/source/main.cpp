#include "../headers/includes.hpp"

#include "../headers/Parser.hpp"
#include "../headers/Instruction.hpp"
#include "../headers/SIM.hpp"

using namespace std;

void parse_input_command(int argc, const char* argv[], int& n, vector<string>& paths){
    // Check if the user provided a file name
        if (argc != 5){
            cerr << "Usage: ./SIM -n N -p <path1,path2,pathN>" << endl;
            exit(-1);
        }

        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-n") == 0) {
                n = atoi(argv[i+1]);
                if (n<1){
                    cerr << "Error: n must be greater than 0" << endl;
                    exit(-2);
                }                
            } else if (strcmp(argv[i], "-p") == 0) {
                string paths_str = argv[i+1];
                string delimiter = ",";
                size_t pos = 0;
                string token;
                while ((pos = paths_str.find(delimiter)) != string::npos) {
                    token = paths_str.substr(0, pos);
                    paths.push_back(token);
                    paths_str.erase(0, pos + delimiter.length());
                }
                paths.push_back(paths_str);
            }
        }
        if (n != paths.size()){
            cerr << "Error: n must be equal to the number of paths" << endl;
            exit(-3);
        }
}

int main(int argc, const char * argv[]) {
    
    int n = 0;
    vector<string> paths;
    parse_input_command(argc, argv, n, paths);
    
    
    // Create a SIM object and run the simulation
    SIM sim(n);

    // Create a parser object and parse the input file
    
    for (int core_id=0; core_id<paths.size(); core_id++){
        int fetched_instructions = 0;
        parser parser(paths[core_id]);
        fetched_instructions  = parser.parse();
        sim.add_instructions(parser.get_instructions(), core_id);
    }

    sim.process();

    return 0;
}
