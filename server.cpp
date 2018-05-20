#include "server.h"

using namespace std;
const int BUFFER_SIZE = 1000;

bool isGetMethod(string header) {
    return (header.find("GET") != std::string::npos);
}

int main(int argc, char *argv[]) {
    if( argc < 3 ) {
        cout << "Za mało argumentow";
        exit(1);
    }

    int port = atoi(argv[1]);
    string dir = argv[2];

    int sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    Bind(sockfd, &server_address, sizeof(server_address));
    Listen(sockfd, 64);


    while (1) {
        int conn_sockfd = Accept(sockfd, NULL, NULL);
        string response;
        char recv_buffer[BUFFER_SIZE + 1];
        Recv(conn_sockfd, recv_buffer, BUFFER_SIZE, 0);
        string recv = recv_buffer;


        if (!isGetMethod(recv)) {
            response = buildNotImplementedResponse();
        } else {
            string path = "./" + dir + extractPath(recv);

            if (isForbiddenPath(path)) {
                response = buildForbiddenResponse();
            } else {
                if( extractPath(recv) == "/" ) {
                    path += "index.html";
                }
                string file = readFileFromPath(path);

                if (file.length()) {
                    if(extractPath(recv) == "/") {
                        response = buildMovedPermanentlyResponse(file, recv);
                    }else {
                        response = buildSuccessResponse(file, recv);
                    }
                } else if ( ! file.length()) {
                    response = buildNotFoundResponse();
                } else {
                    response = buildNotImplementedResponse();
                }
            }
        }

        Send(conn_sockfd, &response[0u], response.length(), 0);
        Close(conn_sockfd);
    }
}
