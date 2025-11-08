#include "storage.h"

#include <stdio.h>
#include <string.h>

char *storage_get(const char *key) {
    for (int i = 0; i < entry_count; ++i) {
        if (strcmp(storage[i].key, key) == 0) {
            return storage[i].value;
        }
    }

    return NULL;
}

_Bool storage_set(const char *key, const char *value) {
    for (int i = 0; i < entry_count; i++) {
        if (strcmp(storage[i].key, key) == 0) {
            strcpy(storage[i].value, value);
            return 1;
        }
    }

    if (entry_count < MAX_ENTRIES) {
        strcpy(storage[entry_count].key, key);
        strcpy(storage[entry_count].value, value);
        entry_count += 1;
        return 1;
    }
    return 0;
}

_Bool storage_del(const char *key) {
    for (int i = 0; i < entry_count; i++) {
        if (strcmp(storage[i].key, key) == 0) {
            for (int j = i; j < entry_count - 1; j++) {
                storage[j] = storage[j + 1];
            }
            entry_count--;
            return 1;
        }
    }
    return 0;
}

Entry *get_full_storage() {
    return storage;
}
