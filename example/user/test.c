#include <stdio.h>
#include <stdlib.h>

#include "easyht.h"


int main(){

    struct hash_table* table = malloc(sizeof(struct hash_table));

    if (init_hash_table(table, 20) < 0){
        perror("Error!\n");
    }


    unsigned i;
    
    unsigned keys[30];

    for (i = 0; i < 30; i++){
        unsigned key = rand();
        keys[i] = key;
        int value = -key;
        put(table, key, value);
    }
    
    for (i = 0; i < 30; i++){
        int* map = get(table, keys[i]);
        if (!map){
            printf("key %u does not exist\n", keys[i]);
            continue;
        }
        printf("%u : %d\n", keys[i], *map);
    }

    for (i = 0; i < 10; i++){
        unsigned key = rand();
        int* map = get(table, key);
        if (!map){
            printf("key %u does not exist\n", key);
            continue;
        }
        printf("%u : %d\n", key, *map);
    }

    free_hash_table(table);

    free(table);

    return 0;
}
