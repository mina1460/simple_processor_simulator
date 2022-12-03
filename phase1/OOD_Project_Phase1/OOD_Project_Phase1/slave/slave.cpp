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
            setup_port(PORT);
            initialize_socket();
            connect_socket();
        }
        void run(){
            while (true){
                std::cout << "Enter instruction number: ";
                std::cin.getline(buffer, BUF_SIZE);
                if (send(master_socket_fd, buffer, BUF_SIZE, 0) < 0){
                    std::cerr << "[x] Error sending message" << std::endl;
                    exit(1);
                }
                if (recv(master_socket_fd, buffer, BUF_SIZE, 0) < 0){
                    std::cerr << "[x] Error receiving message" << std::endl;
                    exit(1);
                }
                std::cout << "Message received: " << buffer << std::endl;
            }
        }
    private:
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
    c.run();
    return 0;
}