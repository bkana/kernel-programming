#include <linux/init.h>
#include <linux/module.h>
//Step 1
#include <linux/moduleparam.h>

//step 2 create variable
int param_var[3] = {0,0,0};

MODULE_LICENSE("GPL");
MODULE_AUTHOR("B. Nguimeya Kana");
MODULE_DESCRIPTION("A Simple Hello World module");
//step 3 register (macro)
//module_param(name_var, type, permissions)

module_param_array(param_var,int,NULL ,S_IRUSR | S_IWUSR);
void display(void)
{
	printk(KERN_ALERT "TEST: param = %d", param_var[0]);
        printk(KERN_ALERT "TEST: param = %d", param_var[1]);
        printk(KERN_ALERT "TEST: param = %d", param_var[2]);
}
static int hello_init(void)
{
	printk(KERN_ALERT "TEST: Hello world, this is kana code\n");
	display();
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "TEST: Good bye , from kana");
}

module_init(hello_init);
module_exit(hello_exit);

