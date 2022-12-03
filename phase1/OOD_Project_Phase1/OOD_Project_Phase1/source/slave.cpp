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
                std::cout << "Enter message: ";
                std::cin.getline(buffer, BUF_SIZE);
                if (send(master_socket_fd, buffer, BUF_SIZE, 0) < 0){
                    std::cerr << "Error sending message" << std::endl;
                    exit(1);
                }
                if (recv(master_socket_fd, buffer, BUF_SIZE, 0) < 0){
                    std::cerr << "Error receiving message" << std::endl;
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

int main(){
    client c;
    c.run();
    return 0;
}