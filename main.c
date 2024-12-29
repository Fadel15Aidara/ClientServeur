#include <stdio.h>
#include<stdlib.h>
#include "common.h"

int main(int argc, char *argv[]) {
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s [server|client]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "server") == 0)
    {
        server();
    } 
    else if (strcmp(argv[1], "client") == 0) 
    {
        client();
    } 
    else 
    {
        fprintf(stderr, "Argument invalide. Utilisez 'server' ou 'client'.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
