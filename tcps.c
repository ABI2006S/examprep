#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int s, ns, n;
    char msg[100];
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    s = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(s, (struct sockaddr *)&server, sizeof(server));
    listen(s, 5);
    printf("Waiting for client...\n");
    ns = accept(s, (struct sockaddr *)&client, &len);

    while (1) {
        n = recv(ns, msg, sizeof(msg)-1, 0);
        if (n <= 0) break;
        msg[n] = '\0';
        printf("Client: %s\n", msg);
        if (strcmp(msg, "exit") == 0) break;

        printf("Server: ");
        fgets(msg, sizeof(msg), stdin);
        msg[strcspn(msg, "\n")] = '\0';
        send(ns, msg, strlen(msg), 0);
        if (strcmp(msg, "exit") == 0) break;
    }

    close(ns);
    close(s);
    return 0;
}