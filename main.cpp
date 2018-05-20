#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>
#include <iostream>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "sockwrap.h"
#include <fstream>
#include <streambuf>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>


using namespace std;

bool isGetMethod(string header) {
    return (header.find("GET") != std::string::npos);
}

string buildResponse(string status, string contentType, string contentLength, string data) {
    return "HTTP/1.1 " + status + " \r\n Content-Type: " + contentType + " \r\n Content-Length: " + contentLength +
           " \r\n\r\n " + data;
}

string createContentType(string header) {
    if (header.find(".html") != std::string::npos) {
        return "text/html";
    }

    if (header.find(".txt") != std::string::npos) {
        return "text/plain";
    }

    if (header.find(".png") != std::string::npos) {
        return "image/png";
    }

    if (header.find(".jpg") != std::string::npos) {
        return "image/jpg";
    }

    if (header.find(".jpeg") != std::string::npos) {
        return "image/jpeg";
    }

    if (header.find(".css") != std::string::npos) {
        return "application/x-pointplus";
    }

    if (header.find(".pdf") != std::string::npos) {
        return "application/pdf";
    }

    return "application/octet-stream";
}

string extractPath(string header) {
    char *header2 = &header[0u];
    string path = "";
    for (int i = 4; header2[i] != ' '; ++i) {
        path += header2[i];
    }

    if (path == "/") path = "/index.html";

    return path;
}

string get_file_string(string path) {
    cout << "PACZAM W SCIEZKE: " << path;
    std::ifstream ifs(path);
    return string((std::istreambuf_iterator<char>(ifs)),
                  (std::istreambuf_iterator<char>()));
}


int main(int argc, char *argv[]) {
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

    const int BUFFER_SIZE = 1000;


    while (1) {
        struct sockaddr_in client_address;
        int conn_sockfd = Accept(sockfd, NULL, NULL);
        string response;
        char recv_buffer[BUFFER_SIZE + 1];

        Recv(conn_sockfd, recv_buffer, BUFFER_SIZE, 0);

        string recv = recv_buffer;


        if (!isGetMethod(recv)) {
            response = buildResponse("501 Not Implemented", "text/plain", "18", "asdasdasd");
        } else {
            string path = "~/" + dir + extractPath(recv);
            response = buildResponse("200 OK", createContentType(recv), "18", "aasdasd");
            cout << get_file_string(path) << endl;//you can do anything with the string!!!
        }

        Send(conn_sockfd, &response[0u], response.length(), 0);

        Close(conn_sockfd);
        printf("Disconnected\n");
    }
}
