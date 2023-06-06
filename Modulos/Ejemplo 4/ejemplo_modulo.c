//Header obligatorio de todos los modulos
#include <linux/module.h>
//Header para usar KERN_INFO
#include <linux/kernel.h>

//Header para las funciones module_init y module_exit
#include <linux/init.h>
//Header necesario porque se usara proc_ops/file_operations
#include <linux/proc_fs.h>
/* Header para usar la lib seq_file y manejar el archivo en /proc*/
#include <linux/seq_file.h>

/* Librerias para lectura de procesos */
#include <linux/sched.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Ejemplo creacion de modulo en Linux, Laboratorio Sistemas Operativos 2");
MODULE_AUTHOR("Bernald Renato Paxtor Peren");


static int escribir_archivo(struct seq_file *archivo, void *v){
    int i=0;
    struct task_struct *task;
    for_each_process(task){
        i++;
    }

    seq_printf(archivo,"Hay %d procesos en el CPU\n", i);


    return 0;
}

//Funcion que se ejecutara cada vez que se lea el archivo con el comando CAT
static int al_abrir(struct inode *inode, struct file *file)
{
    return single_open(file, escribir_archivo, NULL);
}

//Si el kernel es 5.6 o mayor se usa la estructura proc_ops
static struct proc_ops operaciones =
{
    .proc_open = al_abrir,
    .proc_read = seq_read
};

/*Si el kernel es menor al 5.6 usan file_operations
static struct file_operations operaciones =
{
    .open = al_abrir,
    .read = seq_read
};
*/

//Funcion a ejecuta al insertar el modulo en el kernel con insmod
static int _insert(void){
    proc_create("ejemplo_modulo", 0, NULL, &operaciones);
    return 0;
}


//Funcion a ejecuta al remover el modulo del kernel con rmmod
static void _remove(void){
    remove_proc_entry("ejemplo_modulo", NULL);
}

module_init(_insert);
module_exit(_remove);