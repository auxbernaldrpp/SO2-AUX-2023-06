#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Ejemplo creacion de modulo en Linux, Laboratorio Sistemas Operativos 2");
MODULE_AUTHOR("Bernald Renato Paxtor Perén");

static int load_module(void) {
    printk(KERN_INFO "mod: Hola mundo\n");
    return 0;
}

static void unload_module(void) {
    printk(KERN_INFO "mod: Adios mundo!\n");
}

module_init(load_module);
module_exit(unload_module);