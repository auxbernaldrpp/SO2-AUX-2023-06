//Header obligatorio de todos los modulos
#include <linux/module.h>
//Header para usar KERN_INFO
#include <linux/kernel.h>
//Header para las funciones module_init y module_exit
#include <linux/init.h>

/* Libreria para usar si_meminfo */
#include <linux/mm.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Ejemplo creacion de modulo en Linux, Laboratorio Sistemas Operativos 2");
MODULE_AUTHOR("Bernald Renato Paxtor Perén");

//Funcion a ejecuta al insertar el modulo en el kernel con insmod
static int load_module(void){
    struct sysinfo inf;

    si_meminfo(&inf);
    printk(KERN_INFO "ejemplo_modulo: Hola\n");
    printk(KERN_INFO "ejemplo_modulo: Memoria total: %8lu MB\n", inf.totalram * 4/1024);
    return 0;
}


static void unload_module(void){
    printk(KERN_INFO "ejemplo_modulo: Adios\n");
}

module_init(load_module);
module_exit(unload_module);