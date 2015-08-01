#include "easyht.h"

//#define KERNEL

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
    // init every bucket_chain to NULL
    memset(table->bucket_chains_array, 0, anticipated_size * sizeof(struct bucket*));
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
    
    return 0;
}

VALUE_T* get(struct hash_table* table, KEY_T key){
    return NULL;
}

int remove(struct hash_table* table, KEY_T key){
    return 0;
}


