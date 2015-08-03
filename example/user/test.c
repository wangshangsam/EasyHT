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

    // add 30 random key value pairs
    printf("Adding 30 random key value pairs...\n");
    for (i = 0; i < 30; i++){
        unsigned key = rand();
        keys[i] = key;
        int value = -key;
        put(table, key, value);
    }
    
    // print them out
    printf("Printing those 30 newly added key value pairs...\n");
    for (i = 0; i < 30; i++){
        int* map = get(table, keys[i]);
        if (!map){
            printf("key %u does not exist\n", keys[i]);
            continue;
        }
        printf("%u : %d\n", keys[i], *map);
    }

    // print 10 random key
    printf("Printing 10 random key value pairs...\n");
    for (i = 0; i < 10; i++){
        unsigned key = rand();
        int* map = get(table, key);
        if (!map){
            printf("key %u does not exist\n", key);
            continue;
        }
        printf("%u : %d\n", key, *map);
    }

    // remove the first 10 key
    printf("Removing the first 10 keys...\n");
    for (i = 0; i < 10; i++){
        if (erase(table, keys[i]) < 0){
            printf("erase(): key %u does not exist\n", keys[i]);
        }
    }

    // print all out
    printf("Printing all key value pairs...\n");
    for (i = 0; i < 30; i++){
        int* map = get(table, keys[i]);
        if (!map){
            printf("key %u does not exist\n", keys[i]);
            continue;
        }
        printf("%u : %d\n", keys[i], *map);
    }

    // remove 10 random keys
    printf("Removing 10 random key value pairs...\n");
    for (i = 0; i < 10; i++){
        unsigned key = rand();
        if (erase(table, key) < 0){
            printf("erase(): key %u does not exist\n", key);
        }
    }

    // print all out
    printf("Printing all key value pairs...\n");
    for (i = 0; i < 30; i++){
        int* map = get(table, keys[i]);
        if (!map){
            printf("key %u does not exist\n", keys[i]);
            continue;
        }
        printf("%u : %d\n", keys[i], *map);
    }

    free_hash_table(table);
    free(table);

    return 0;
}
