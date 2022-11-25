#include "../headers/includes.hpp"

#include "../headers/Parser.hpp"
#include "../headers/Instruction.hpp"
#include "../headers/SIM.hpp"

using namespace std;

void parse_input_command(int argc, const char* argv[], int& n, vector<string>& paths){
    
        if (argc == 3){
            if (strcmp(argv[1], "-d") == 0){
                //open directory and get files
                string path = argv[2];
                DIR *dir;
                struct dirent *ent;
                if ((dir = opendir (path.c_str())) != NULL) {
                    // get all the .txt files within directory
                    while ((ent = readdir (dir)) != NULL) {
                        string file_name = ent->d_name;
                        if (file_name.find(".txt") != string::npos){
                            cout << "Program file: " << path + "/" + file_name << endl;
                            paths.push_back(path + "/" + file_name);
                        }
                    }
                    closedir (dir);
                    n = paths.size();   // getting the number of threads
                } else {
                    // could not open directory
                    cerr << "Error: could not open directory" << endl;
                    exit(-5);
                }
            } else {
                cerr << "Usage: ./SIM -d <directory_path>" << endl;
                exit(-4);
            }
        }
        else if (argc == 5){
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
        } else {
            cerr << "Usage: \n\t./SIM -d <directory_path>\n\t./SIM -n N -p <file_path1,file_path2,file_pathN>" << endl;
            exit(-1);
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
