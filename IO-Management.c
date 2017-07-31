#include <linux/module.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>

MODULE_LICENSE("GPL");

static struct cdev *driver_object=NULL;

static struct file_operations fops = {
	.owner=THIS_MODULE,
};

static int myregister_chrdev(dev_t device_number, int count, char *name,
struct file_operations *fops){

if(register_chrdev_region(device_number, count, name)){
 printk("Devicenumber 0x%x not available ...\n", device_number);
 return -1;
}
driver_object = cdev_alloc();
if(driver_object==NULL){
 printk("cdev_alloc failed ...\n");
 goto free_device_number;
}
kobject_set_name(&driver_object->kobj, name);
driver_object->owner = THIS_MODULE;
cdev_init(driver_object, fops);
if(cdev_add(driver_object, device_number, count)){
 printk("cdev_add failed ...\n");
 goto free_cdev;
}
return 0;

free_cdev:
	kobject_put(&driver_object->kobj);
	driver_object = NULL;
free_device_number:
	unregister_chrdev_region(device_number, count);
	return -1;
}

int myunregister_chrdev(dev_t device_number, int count)
{
	if(driver_object)
	cdev_del(driver_object);
	unregister_chrdev_region(device_number, count);
	return 0;
}

static int __init buf_init(void)
{
	if(myregister_chrdev(MKDEV(241,0),300, "300Devices", &fops) == 0) {
	return 0;
}
return -EIO;
}

static void __exit buf_exit(void)
{
	dev_t device_number = MKDEV(241,0);
	if(driver_object)
	myunregister_chrdev(device_number, 300);
}

module_init(buf_init);
module_exit(buf_exit);
