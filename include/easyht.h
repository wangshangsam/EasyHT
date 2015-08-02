#ifndef EASYHT_H
#define EASYHT_H

#define KEY_T       unsigned
#define VALUE_T     int

// error code defination
#define SUCCESS 0
#define KEY_EXISTED 201
#define KEY_NOT_FOUND 202

struct bucket{
    KEY_T key;
    VALUE_T value;
    struct bucket* next;
};

struct hash_table{
    unsigned num_bucket;
    unsigned array_size;
    struct bucket** bucket_chains_array;
};

int init_hash_table(struct hash_table* table, unsigned anticipated_size);

void free_hash_table(struct hash_table* table);

int put(struct hash_table* table, KEY_T key, VALUE_T value);

VALUE_T* get(struct hash_table* table, KEY_T key);

int erase(struct hash_table* table, KEY_T key);

#endif
