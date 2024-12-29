#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "common.h"

void server() 
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
     Donne Dt;
      Dt.compteur = 0;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Erreur creation de socket");
        exit(EXIT_FAILURE);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Erreur de Bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
   if (listen(server_fd, 5) == -1)
    {
        perror("Erreur de Listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("le Server ecoute le port %d\n", PORT);

    if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len)) == -1)
      {
        perror("Erreur de Accept ");
        close(server_fd);
        exit(EXIT_FAILURE);
      }
      printf("Client connected\n");

    while (1)
    {
     
        if (send(client_fd, &Dt, sizeof(Dt), 0) == -1)
        {
            perror("Erreur du Send ");
            break;
        }

        if (recv(client_fd, &Dt, sizeof(Dt), 0) <= 0)
        {
            perror("Erreur de Receive");
            break;
        }
         printf("Recevoir compteur du client: %d\n", Dt.compteur);
        Dt.compteur++;
        printf(" Compteur incremente: %d\n", Dt.compteur);

        sleep(1);
    }

    close(client_fd);
    close(server_fd);
}
