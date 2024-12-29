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

void  client()
{
    int client_fd;
    struct sockaddr_in server_addr;
    Donne Dt;

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0)
    {
        perror("Adresse invalide");
        close(client_fd);
        exit(EXIT_FAILURE);
    }
   
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    while (1)
     {
        
        if (recv(client_fd, &Dt, sizeof(Dt), 0) <= 0)
         {
            perror("Erreur de reception \n");
            break;
         }
          printf("le compteur recu : %d\n", Dt.compteur);

        Dt.compteur++;
        printf("Compteur  incremente: %d\n",Dt.compteur);

        sleep(1);

        if (send(client_fd, &Dt, sizeof(Dt), 0) == -1)
          {
            perror("Erreur d'envoi");
            break;
          }
      }
       close(client_fd);

}

