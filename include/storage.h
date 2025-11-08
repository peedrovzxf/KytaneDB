#ifndef KYTANE_DB_STORAGE_H
#define KYTANE_DB_STORAGE_H

#define MAX_ENTRIES 128
#define MAX_KEY_LEN 64
#define MAX_VALUE_LEN 256

typedef struct {
    char key[MAX_KEY_LEN];
    char value[MAX_VALUE_LEN];
} Entry;

static Entry storage[MAX_ENTRIES];
static int entry_count = 0;

char *storage_get(const char *key);
_Bool storage_set(const char *key, const char *value);
_Bool storage_del(const char *key);

Entry *get_full_storage();

#endif //KYTANE_DB_STORAGE_H