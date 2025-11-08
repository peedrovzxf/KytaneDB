#ifndef KYTANE_DB_SERVER_H
#define KYTANE_DB_SERVER_H

#define BUFFER_SIZE 1024

void server_start(int port);

void sanitize_line(int bytes, char buffer[BUFFER_SIZE]);

#endif //KYTANE_DB_SERVER_H