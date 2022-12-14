#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> //sockaddr, socklen_t
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "../headers/Parser.hpp"
#include "../headers/Core.hpp"


#define PORT 8080
#define BUF_SIZE 128

class client{
    public:
        void setup_port(int port){
            master_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
            if (master_socket_fd < 0){
                std::cout << "Error creating socket" << std::endl;
                exit(1);
            }
            std::cout << "Socket created" << std::endl;
            bzero((char *) &server_addr, sizeof(server_addr));
            server_addr.sin_family = AF_INET;
            server_addr.sin_addr.s_addr = INADDR_ANY;
            server_addr.sin_port = htons(port);
            bzero(buffer, BUF_SIZE);
        }
        void initialize_socket(){
            int multi = 1;
            // TCP_NODELAY is a socket option that disables the Nagle algorithm.
            // Nagle's algorithm is a heuristic algorithm used to improve the efficiency of TCP/IP networks by reducing the number of packets sent.
            // set TCP_NODELAY to 1 to disable Nagle's algorithm
            
            if (setsockopt(master_socket_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&multi, sizeof(multi)) < 0){
                std::cerr << "Error setting socket options" << std::endl;
                exit(1);
            }

        }
        void connect_socket(){
            if (connect(master_socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
                std::cerr << "Error connecting to socket" << std::endl;
                exit(1);
            }
        }
        client(){
            std::array<std::atomic<int32_t>, DATA_MEMORY_SIZE> data_memory; 
            core = new Core(1, &data_memory);
            setup_port(PORT);
            initialize_socket();
            connect_socket();
        }
        void run(std::vector<int>& instruction_number){
            for(int i=0; i<instruction_number.size(); i++){
                
                memset(buffer, 0, BUF_SIZE);
                std::string input;
                input = std::to_string(instruction_number[i]);
                std::cout << "Requesting instruction number: " << input << std::endl;

                if (send(master_socket_fd, input.c_str(), input.length(), 0) < 0){
                    std::cerr << "Error sending to socket" << std::endl;
                    exit(1);
                }
                
                if (recv(master_socket_fd, buffer, BUF_SIZE, 0) < 0){
                    std::cerr << "[x] Error receiving message" << std::endl;
                    exit(1);
                }
                
                try{
                    std::string instruction_str = buffer;
                    std::cout << "Instruction string: " << instruction_str << "." << std::endl;
                    Instruction* instruction = parser.prepare_instruction(instruction_str);
                    std::vector<Instruction*> instructions;
                    instructions.push_back(instruction);
                    core->add_instructions(instructions);
                    core->process();
                    if(instruction->get_opcode() == HLT_OPCODE){
                        break;
                    }
                    
                }
                catch (const std::exception& e){
                    std::cout << "Error parsing instruction" << std::endl;
                    std::cout << e.what() << std::endl;
                    i--;
                }
                
            }
        }
    private:
        Core* core;
        parser parser;
        int master_socket_fd;
        struct sockaddr_in server_addr;
        char buffer[BUF_SIZE];
};

std::vector<int> get_slave_instruction_numbers(std::string path){
    std::vector<int> instruction_numbers;
    std::ifstream file(path);
    if(!file.is_open()){
        std::cerr << "Error opening file" << std::endl;
        exit(1);
    }
    std::string line;
    while (std::getline(file, line)){
        instruction_numbers.push_back(std::stoi(line));
    }
    return instruction_numbers;
}

int main(int argc, char* argv[]){
    if (argc != 2){
        std::cerr << "Usage: ./client <path_to_file>" << std::endl;
        exit(1);
    }
    std::vector<int> instruction_numbers = get_slave_instruction_numbers(argv[1]);
    client c;
    
    c.run(instruction_numbers);
    return 0;
}