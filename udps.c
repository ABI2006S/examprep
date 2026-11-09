#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  int s, n;
  char msg[100];
  struct sockaddr_in server, client;
  socklen_t len = sizeof(client);

  s = socket(AF_INET, SOCK_DGRAM, 0);
  server.sin_family = AF_INET;
  server.sin_port = htons(8080);
  server.sin_addr.s_addr = INADDR_ANY;
  bind(s, (struct sockaddr *)&server, sizeof(server));

  while (1) {
    n = recvfrom(s, msg, sizeof(msg) - 1, 0, (struct sockaddr *)&client, &len);
    if (n < 0)
      break;
    msg[n] = '\0';
    printf("Client: %s\n", msg);
    if (strcmp(msg, "exit") == 0)
      break;

    printf("Server: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = '\0';
    sendto(s, msg, strlen(msg), 0, (struct sockaddr *)&client, len);
    if (strcmp(msg, "exit") == 0)
      break;
  }

  close(s);
  return 0;
}