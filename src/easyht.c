#include "easyht.h"

#define KERNEL

#ifdef KERNEL // include the kernel headers

#include <linux/slab.h>
#include <linux/string.h>

#define malloc(size) \
    kmalloc(size, GFP_KERNEL)

#define free(ptr) \
    kfree(ptr)

#else

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#endif

static unsigned hash(KEY_T key, unsigned array_size){
    unsigned converted;

    converted = *((unsigned*)(&key));

    return converted % array_size;
}

int init_hash_table(struct hash_table* table, unsigned anticipated_size){
    memset(table, 0, sizeof(struct hash_table));
    table->num_bucket = 0;
    table->array_size = anticipated_size;
    table->bucket_chains_array = malloc(anticipated_size * sizeof(struct bucket*));
    
    if (!table->bucket_chains_array){
        return -ENOMEM;
    }

    // init every bucket_chain to NULL
    memset(table->bucket_chains_array, 0, anticipated_size * sizeof(struct bucket*));
    return SUCCESS;
}

// recursively free the collection of buckets on one bucket chain
static void free_bucket_chain(struct bucket* p_bucket){
    if (!p_bucket){ // p_bucket == NULL
        return;
    }
    else{
        free_bucket_chain(p_bucket->next);
        free(p_bucket);
        return;
    }
}

void free_hash_table(struct hash_table* table){
    // free every bucket 
    unsigned i;
    for (i = 0; i < table->array_size; i++){
        free_bucket_chain(table->bucket_chains_array[i]);
    }
    // free the bucket_chains_array itself
    free(table->bucket_chains_array);
    table->bucket_chains_array = NULL;
    table->num_bucket = 0;
    table->array_size = 0;
}

int put(struct hash_table* table, KEY_T key, VALUE_T value){

    unsigned index = hash(key, table->array_size);

    struct bucket* cursor = NULL;
    struct bucket* new_bucket = NULL;

    // check if the bucket chain is empty
    if (!(table->bucket_chains_array[index])){ // if bucket_chains_array[index] == NULL, bucket chain
        // is empty, create the first bucket
        table->bucket_chains_array[index] = malloc(sizeof(struct bucket));
        if (!(table->bucket_chains_array[index])){
            return -ENOMEM;
        }
        table->bucket_chains_array[index]->key = key;
        table->bucket_chains_array[index]->value = value;
        table->bucket_chains_array[index]->next = NULL;
        return SUCCESS;
    }

    // linear search 
    for (cursor = table->bucket_chains_array[index]; cursor->next != NULL; cursor = cursor->next){
        if (cursor->key == key){
            goto key_existed;
        }
    }
    
    // right now cursor pointing to the tail

    if (cursor->key == key){ // check the tail
        goto key_existed;
    }

    // the key is indeed a new key

    new_bucket = malloc(sizeof(struct bucket));

    if (!new_bucket){
        return -ENOMEM;
    }

    new_bucket->key = key;
    new_bucket->value = value;
    new_bucket->next = NULL;
    cursor->next = new_bucket;
    return SUCCESS;

key_existed:
    return -KEY_EXISTED;
}

VALUE_T* get(struct hash_table* table, KEY_T key){
    unsigned index = hash(key, table->array_size);

    struct bucket* cursor = NULL;

    if (!(table->bucket_chains_array[index])){
        return NULL;
    }

    for (cursor = table->bucket_chains_array[index]; cursor != NULL; cursor = cursor->next){
        if (cursor->key == key){
            return &(cursor->value);
        }
    }
    
    return NULL;
}

int erase(struct hash_table* table, KEY_T key){
    return 0;
}


