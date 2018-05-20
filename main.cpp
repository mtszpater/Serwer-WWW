#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>


int Socket(int family, int type, int protocol) {
    int n;
    if ((n = socket(family, type, protocol)) < 0)
        printf("socket error");
    return n;
}

void Bind(int fd, const struct sockaddr_in *sa, socklen_t salen) {
    if (bind(fd, (struct sockaddr *) sa, salen) < 0)
        printf("bind error");
}

void Connect(int fd, const struct sockaddr_in *sa, socklen_t salen) {
    if (connect(fd, (struct sockaddr *) sa, salen) < 0)
        printf("connect error");
}

int Accept(int fd, struct sockaddr_in *sa, socklen_t *salenptr) {
    int n;
    if ((n = accept(fd, (struct sockaddr *) sa, salenptr)) < 0)
        printf("accept error");
    return n;
}

void Listen(int fd, int backlog) {
    if (listen(fd, backlog) < 0)
        printf("listen error");
}

ssize_t Recv(int fd, char *ptr, size_t nbytes, int flags) {
    int n;
    if ((n = recv(fd, ptr, nbytes, flags)) < 0)
        printf("recv error");
    ptr[n] = 0;
    return n;
}

void Send(int fd, char *ptr, int nbytes, int flags) {
    // to niekoniecznie jest blad!
    if (send(fd, ptr, nbytes, flags) < nbytes)
        printf("send error");
}

void Close(int fd) {
    if (close(fd) < 0)
        printf("close error");
}

int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout) {
    int n;
    if ((n = select(nfds, readfds, writefds, exceptfds, timeout)) < 0)
        printf("select error");
    return n;
}

int main() {
    int sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8888);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    Bind(sockfd, &server_address, sizeof(server_address));
    Listen(sockfd, 64);

    while (1) {
        // accept() jak poprzednio, ale wypisujemy informacje na temat klienta
        struct sockaddr_in client_address;

        int conn_sockfd = Accept(sockfd, NULL, NULL);
        char ip_address[20];


        const int BUFFER_SIZE = 1000;
        char recv_buffer[BUFFER_SIZE + 1];


        Recv(conn_sockfd, recv_buffer, BUFFER_SIZE, 0);

        for (int i = 0; i < BUFFER_SIZE; ++i) {
            printf("%c", recv_buffer[i]);
        }

        Close(conn_sockfd);
        printf("Disconnected\n");
    }
}
