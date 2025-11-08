#include <stdio.h>
#include <string.h>
#include "storage.h"

char *handle_command(const char* input) {
    if (strcmp(input, "PING") == 0) {
        return "PONG";
    }

    if (strncmp(input, "GET", 3) == 0) {
        char key[MAX_KEY_LEN];
        if (sscanf(input + 3, " %63s", key) == 1) {
            char *result = storage_get(key);
            if (result == NULL) {
                return "(nil)";
            }

            return result;
        }
        return "ERR wrong number of arguments";
    }

    if (strncmp(input, "SET", 3) == 0) {
        char key[MAX_KEY_LEN];
        char value[MAX_VALUE_LEN];
        if (sscanf(input + 3, " %63s %255[^\n]", key, value) == 2) {
            return storage_set(key, value) ? "Value updated" : "Storage full";
        }
        return "ERR wrong number of arguments";
    }

    if (strncmp(input, "DEL", 3) == 0) {
        char key[MAX_KEY_LEN];
        if (sscanf(input + 3, " %63s", key) == 1) {
            return storage_del(key) ? "Value deleted" : "Value did not exist";
        }
        return "ERR wrong number of arguments";
    }

    if (strcmp(input, "PRINT") == 0) {
        return print_storage();
    }

    if (strcmp(input, "SHUTDOWN") == 0) {
        return "\0";
    }

    return "ERR unknown command";
}
