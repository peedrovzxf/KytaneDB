#include "server.h"
#include "handler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

void server_start(const int port) {
    printf("Starting server on port %d...", port);

    const int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    const int opt = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(socket_fd, 1) == -1) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    int running = 1;
    while (running) {
        socklen_t socklen = sizeof(server_addr);
        const int client_fd = accept(socket_fd, (struct sockaddr*)&server_addr, &socklen);
        if (client_fd == -1) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        char buffer[BUFFER_SIZE];
        const int bytes = (int) recv(client_fd, buffer, sizeof(buffer), 0);
        if (bytes == -1) {
            perror("An error happened when trying to read bytes from socket.");
            exit(EXIT_FAILURE);
        }

        if (bytes > 0) {
            sanitize_line(bytes, buffer);
            printf("> '%s'\n", buffer);

            const char *result = handle_command(buffer);
            send(client_fd, result, strlen(result), MSG_NOSIGNAL);
            send(client_fd, "\n", 1, MSG_NOSIGNAL);
            if (strcmp("SHUTDOWN", buffer) == 0) {
                printf("Server is being stopped.\n");
                running = 0;
            }
        }
        close(client_fd);
    }
    close(socket_fd);
}

void sanitize_line(const int bytes, char buffer[BUFFER_SIZE]) {
    if (buffer[bytes -1] == '\n') {
        buffer[bytes - 1] = '\0';
        return;
    }
    buffer[bytes] = '\0';
}
