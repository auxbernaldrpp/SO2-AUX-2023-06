//Header obligatorio de todos los modulos
#include <linux/module.h>
//Header para usar KERN_INFO
#include <linux/kernel.h>

//Header para las funciones module_init y module_exit
#include <linux/init.h>
//Header necesario porque se usara proc_fs
#include <linux/proc_fs.h>
/* Header para usar la lib seq_file y manejar el archivo en /proc*/
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Ejemplo creacion de modulo en Linux, Laboratorio Sistemas Operativos 2");
MODULE_AUTHOR("Bernald Renato Paxtor Perén");


static int escribir_archivo(struct seq_file *archivo, void *v){
    seq_printf(archivo, "*********************************************\n");
    seq_printf(archivo, "*********************************************\n");
    seq_printf(archivo, "**********EJEMPLO SO2 VAC JUN 2023***********\n");
    seq_printf(archivo, "*********************************************\n");
    seq_printf(archivo, "*********************************************\n");
    return 0;
}

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

static int _insert(void){
    proc_create("ejemplo_modulo", 0, NULL, &operaciones);
    return 0;
}



static void _remove(void){
    remove_proc_entry("ejemplo_modulo", NULL);
}

module_init(_insert);
module_exit(_remove);