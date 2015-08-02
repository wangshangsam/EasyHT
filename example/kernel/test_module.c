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
    printk(KERN_INFO "test_init() starts\n");

    struct hash_table* table = malloc(sizeof(struct hash_table));

    if (init_hash_table(table, 20) < 0){
        printk(KERN_ERR "Error!\n");
    }


    unsigned i;

    unsigned keys[30];

    for (i = 0; i < 30; i++){
        unsigned key = 0;

        get_random_bytes(&key, sizeof(unsigned));
        
        unsigned mask = 0x7FFFFFFF;
        key = key & mask;

        keys[i] = key;
        int value = -key;
        put(table, key, value);
    }

    for (i = 0; i < 30; i++){
        int* map = get(table, keys[i]);
        if (!map){
            printk(KERN_INFO "key %u does not exist\n", keys[i]);
            continue;
        }
        printk(KERN_INFO "%u : %d\n", keys[i], *map);
    }

    for (i = 0; i < 10; i++){
        unsigned key = 0;
        
        get_random_bytes(&key, sizeof(unsigned));

        int* map = get(table, key);
        if (!map){
            printk(KERN_INFO "key %u does not exist\n", key);
            continue;
        }
        printk(KERN_INFO "%u : %d\n", key, *map);
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
