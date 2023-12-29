#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h> // Include the errno header

#define PORT 8080
#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024

int main() {
    int server_socket, new_socket, client_sockets[MAX_CLIENTS], activity, i, valread, sd;
    int max_sd;
    struct sockaddr_in address;
    socklen_t addrlen; // Declare addrlen

    fd_set readfds;

    // ... (rest of the code)

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(server_socket, &readfds);
        max_sd = server_socket;

        for (i = 0; i < MAX_CLIENTS; i++) {
            sd = client_sockets[i];

            if (sd > 0) {
                FD_SET(sd, &readfds);
            }

            if (sd > max_sd) {
                max_sd = sd;
            }
        }

        // Wait for an activity on any of the sockets
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR)) {
            perror("Select error");
            // Handle the error or exit as needed
            exit(EXIT_FAILURE);
        }

        // ... (rest of the code)
    }

    return 0;
}

