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
#include "../headers/Parser.hpp"

#define PORT 8080
#define BUF_SIZE 128
#define MAX_CONCURRENT_CLIENTS 5
class server{
    public:
        void setup_port(int port){
            master_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
            if (master_socket_fd < 0){
                std::cout << "Error creating socket" << std::endl;
                exit(1);
            }
            std::cout << "Socket created" << std::endl;
            FD_ZERO(&read_fds);
            FD_ZERO(&master_fds);
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
        void bind_socket(){
            if (bind(master_socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
                std::cerr << "Error binding socket" << std::endl;
                exit(1);
            }
            FD_SET(master_socket_fd, &master_fds);
            max_fd = master_socket_fd;
        }
        
        void listen_socket(){
            if (listen(master_socket_fd, MAX_CONCURRENT_CLIENTS) < 0){
                std::cerr << "Error listening on socket" << std::endl;
                exit(1);
            }
        }

        server(){
            setup_port(PORT);
            initialize_socket();
            bind_socket();
            listen_socket();
        }
        

        server(int port){
            setup_port(port);
            initialize_socket();
            bind_socket();
            listen_socket();
        }

        ~server(){
            close(master_socket_fd);
        }

        void run(){
            while (true){
                read_fds = master_fds;
                if (select(max_fd+1, &read_fds, NULL, NULL, NULL) < 0){
                    std::cerr << "Error selecting socket" << std::endl;
                    exit(1);
                }
                for (int i = 0; i <= max_fd; i++){
                    if (FD_ISSET(i, &read_fds)){
                        if (i == master_socket_fd){
                            // new connection
                            int new_socket_fd;
                            struct sockaddr_in client_addr;
                            socklen_t client_addr_len = sizeof(client_addr);
                            if ((new_socket_fd = accept(master_socket_fd, (struct sockaddr *) &client_addr, &client_addr_len)) < 0){
                                std::cerr << "Error accepting new connection" << std::endl;
                                exit(1);
                            }
                            FD_SET(new_socket_fd, &master_fds);
                            if (new_socket_fd > max_fd){
                                max_fd = new_socket_fd;
                            }
                            std::cout << "New connection from " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << std::endl;
                        } else {
                            // existing connection
                            int bytes_read;
                            if ((bytes_read = recv(i, buffer, BUF_SIZE, 0)) <= 0){
                                if (bytes_read == 0){
                                    std::cout << "Connection closed" << std::endl;
                                } else {
                                    std::cerr << "Error reading from socket" << std::endl;
                                }
                                close(i);
                                FD_CLR(i, &master_fds);
                            } else {
                                std::cout << "Client #" << i << ": " << buffer << std::endl;
                                std::cout << "Received: " << buffer << std::endl;
                                if (send(i, buffer, bytes_read, 0) < 0){
                                    std::cerr << "Error sending to socket" << std::endl;
                                    exit(1);
                                }
                            }
                        }
                    }
                }
            }
        }
    private:
        
        fd_set master_fds;
        fd_set read_fds;

        uint16_t max_fd; //max file descriptor number

        int master_socket_fd; //master socket file descriptor
        int read_socket_fd; //read socket file descriptor

        struct sockaddr_in server_addr;
        struct sockaddr_storage client_addr;

        char buffer[BUF_SIZE];
        int nbytes;

        char remoteIP[INET6_ADDRSTRLEN];
};

int main(int argc, char *argv[]){
    if(argc < 2){
        std::cout << "Usage: ./server code_path" << std::endl;
        exit(1);
    }
    std::string code_path = argv[1];
    parser parser(code_path);
    parser.parse();
    std::cout << "Parser initialized" << std::endl;
    std::vector<Instruction*>& p_instructions = parser.get_instructions();
    for(auto& instruction : p_instructions){
        std::cout << instruction->get_instruction_str() << std::endl;
    }
    server s;
    s.run();
    return 0;
}