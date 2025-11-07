#include <stdio.h>
#include "server.h"

int main() {
    printf("Welcome to Kytane-DB!\n");
    server_start(6379);
    return 0;
}