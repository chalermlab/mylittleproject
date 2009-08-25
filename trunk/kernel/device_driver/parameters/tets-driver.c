
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

MODULE_DESCRIPTION("My kernel module");
MODULE_AUTHOR("Fredrik Svärd (fredrik@dronten)");
MODULE_LICENSE("$LICENSE$");

/* A couple of parameters that could be passed in: how many times and to whom we say hello */

static char *whom = "world";
module_param(whom, charp, 0);

static int how_many = 1;
module_param(how_many, int, 0);


static int tets_init_module(void)
{
	int i;
	for (i=0;i<how_many;i++)
		printk( KERN_DEBUG "(%d) Hello, %s\n", i, whom);
	return 0;
}

static void tets_exit_module(void)
{
	printk( KERN_DEBUG "Godbye cruel %s\n", whom);
}

module_init(tets_init_module);
module_exit(tets_exit_module);
