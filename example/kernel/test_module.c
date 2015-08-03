#include "easyht.h"
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/random.h>

#define malloc(size) \
    kmalloc(size, GFP_KERNEL)

#define free(ptr) \
    kfree(ptr)

static int __init test_init(void){
   
    unsigned mask = 0x7FFFFFFF;
    
    printk(KERN_INFO "test_init() starts\n");

    struct hash_table* table = malloc(sizeof(struct hash_table));

    if (init_hash_table(table, 20) < 0){
        printk(KERN_ERR "Error!\n");
    }


    unsigned i;

    unsigned keys[30];

    // add 30 random key value pairs
    printk(KERN_INFO "Adding 30 random key value pairs...\n");
    for (i = 0; i < 30; i++){
        unsigned key = 0;

        get_random_bytes(&key, sizeof(unsigned));
        key = key & mask;

        keys[i] = key;
        int value = -key;
        put(table, key, value);
    }

    // print them out
    printk(KERN_INFO "Printing those 30 newly added key value pairs...\n");
    for (i = 0; i < 30; i++){
        int* map = get(table, keys[i]);
        if (!map){
            printk(KERN_INFO "key %u does not exist\n", keys[i]);
            continue;
        }
        printk(KERN_INFO "%u : %d\n", keys[i], *map);
    }

    // print 10 random keys
    printk(KERN_INFO "Printing 10 random key value pairs...\n");
    for (i = 0; i < 10; i++){
        unsigned key = 0;
        
        get_random_bytes(&key, sizeof(unsigned));
        key = key & mask;

        int* map = get(table, key);
        if (!map){
            printk(KERN_INFO "key %u does not exist\n", key);
            continue;
        }
        printk(KERN_INFO "%u : %d\n", key, *map);
    }

    // remove the first 10 key
    printk(KERN_INFO "Removing the first 10 keys...\n");
    for (i = 0; i < 10; i++){
        if (erase(table, keys[i]) < 0){
            printk(KERN_ERR "erase(): key %u does not exist\n", keys[i]);
        }
    }

    // print all out
    printk(KERN_INFO "Printing all key value pairs...\n");
    for (i = 0; i < 30; i++){
        int* map = get(table, keys[i]);
        if (!map){
            printk(KERN_INFO "key %u does not exist\n", keys[i]);
            continue;
        }
        printk(KERN_INFO "%u : %d\n", keys[i], *map);
    }

    // remove 10 random keys
    printk(KERN_INFO "Removing 10 random key value pairs...\n");
    for (i = 0; i < 10; i++){
        unsigned key = 0;
        
        get_random_bytes(&key, sizeof(unsigned));
        key = key & mask;

        if (erase(table, key) < 0){
            printk(KERN_ERR "erase(): key %u does not exist\n", key);
        }
    }

     // print all out
    printk(KERN_INFO "Printing all key value pairs...\n");
    for (i = 0; i < 30; i++){
        int* map = get(table, keys[i]);
        if (!map){
            printk(KERN_INFO "key %u does not exist\n", keys[i]);
            continue;
        }
        printk(KERN_INFO "%u : %d\n", keys[i], *map);
    }


    free_hash_table(table);
    free(table);

    printk(KERN_INFO "test_init() ends\n");
    return 0;
}

static void __exit test_exit(void){
    printk(KERN_INFO "test_exit() starts\n");

    printk(KERN_INFO "test_exit() ends\n");
}

module_init(test_init);
module_exit(test_exit);

MODULE_AUTHOR("Sam");
MODULE_LICENSE("GPL");
