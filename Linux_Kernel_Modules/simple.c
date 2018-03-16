/** Used to print appropraite messages when a kernel module is loaded and unloaded */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/slab.h>

typedef struct birthday {
	int day;
	int month;
	int year; 
	struct list_head list;
} birthday;

static LIST_HEAD(birthday_list); // birthday_list = struct list_head object that will point to the head of person

int simple_init(void)
{
	/** Moduel entry point -- invoked when module is loaded (insmod simple.ko).
	 * It uses the kernel linked-list data structure and logs values to the kernel.
	 */
	
	int i; 
	birthday *ptr; // pointer to traverse the birthday structure
	
	printk(KERN_INFO "Loading Module\n");
	
	i = 1;
	while (i <= 5)
	{
		birthday *person;
		person = (birthday *) kmalloc(sizeof(*person), GFP_KERNEL);  // allocates kernel memory to person
		person->day = 9 + i;
		person->month = 10 + i;
		person->year = 1994 + i;
		INIT_LIST_HEAD(&person->list); // initializes the 'list' member of person
	
		list_add_tail(&person->list, &birthday_list); // add person to the end of the linked list whose head is birthday_list	
		
		i++;
	}	
	
	list_for_each_entry(ptr, &birthday_list, list)
	{
		/** Remove all the entries of the linked list
		Parameters:
			* ptr -> pointer to iterate over the elements of the linked-list
			* &birthday_list -> address of the head of the linked-list to traverse
			* list -> name of the struct list_head member of the structure
		*/
		printk("DOB: %d / %d / %d\n", ptr->day, ptr->month, ptr->year);
	}
	
	return 0; // success
}


void simple_exit(void)
{
	/** Module exit point -- called when module is removed (rmmod simple.ko or rmmod simple).
	* It removes all the elements of the kernel linked-list, before removing the linked-list.*/
	
	birthday *ptr, *next;
	
	printk(KERN_INFO "Removing Module\n");
	
	list_for_each_entry_safe(ptr, next, &birthday_list, list)
	{
		/** Remove all the entries of the linked list
		Parameters:
			* ptr -> pointer to iterate over the elements of the linked-list
			* next -> pointer containing the address of the next entry of the linked-list (required for preservation of structure after deletion)
			* &birthday_list -> address of the head of the linked-list to traverse
			* list -> name of the struct list_head member of the structure
		*/
		printk(KERN_INFO "DOB deleted: %d / %d / %d\n", ptr->day, ptr->month, ptr->year);
		list_del(&ptr->list);
		
		kfree(ptr); // return the freed memory back to the kernel memory pool
	}
}

// Macros for registering module entry and exit points
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("Only to avoid the warning; I'm not licensing this module");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("Rafi");

