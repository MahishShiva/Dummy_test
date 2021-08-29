#include<linux/kobject.h>
#include<linux/string.h>
#include<linux/sysfs.h>
#include <linux/module.h>
#include <linux/init.h>

//creating module in sysfs at mentioned path --->/sys/kernel/kobject_test
//inside which 2 files are created with name test1,test2.
//if an integer is written to these files it can be later read out of it.


//test1,test2 attributes are associated with these test1,test2 variables respectively.
static int test1;
static int test2;

// a typical show call-back which is associated with the attribute{}/kobj_attribute{}
//and test1,test2 variable.
static ssize_t b_show(struct kobject *kobj, struct kobj_attribute *attr,
		      char *buf)
{
	int var;
        dump_stack();

	if (strcmp(attr->attr.name, "test1") == 0)
		var = test1;
	else
		var = test2;
	return sprintf(buf, "%d\n", var);
}

// a typical show call-back which is associated with the attribute{}/kobj_attribute{}
//and test1,test2 variable.
static ssize_t b_store(struct kobject *kobj, struct kobj_attribute *attr,
		       const char *buf, size_t count)
{
	int var;
        dump_stack();

	sscanf(buf, "%du", &var);
	if (strcmp(attr->attr.name, "test1") == 0)
		test1 = var;
	else{	
		printk(KERN_ALERT "ATTRIBUTE IS ALLOWED ONLY FOR READ PERMISSION\n");
		//return NULL;
	}
	return count;
}

//device specific attribute
static struct kobj_attribute test1_attribute=
		__ATTR(test1,0600,b_show,b_store);
static struct kobj_attribute test2_attribute=
		__ATTR(test2,0400,b_show,b_store);
		
static struct kobject *example_kobj;

static int __init example_init(void)
{
	int retval=0,rt1,rt2;
	dump_stack();
	//creating a kobject and registering it
	example_kobj=kobject_create_and_add("kobject_test",kernel_kobj);
	if(!example_kobj)	//error checking
			return -ENOMEM;
			 
	rt1=sysfs_create_file(example_kobj,&test1_attribute.attr);
	rt2=sysfs_create_file(example_kobj,&test2_attribute.attr);
	if(rt1 && rt2){	//error checking
		
		kobject_put(example_kobj);
	}
	retval=rt1&rt2;
	printk(KERN_ALERT "MODULE HAS BEEN LOADED SUCESSFULLY...!\n");
	return retval;
}

static void __exit example_exit(void)
{
	dump_stack();
	kobject_put(example_kobj);	//resource deallocation
	printk(KERN_ALERT "MODULE HAS BEEN REMOVED SUCESSFULLY...!\n");
}

//data for loader
module_init(example_init);
module_exit(example_exit);
//license related data 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Greg Kroah-Hartman <greg@kroah.com>");
	

