//
//  
//  
//
//  Created by 费克翔 on 20

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/moduleparam.h>

static int pid;

module_param(pid,int,0644);

MODULE_LICENSE("GPL");

static int dePreFa_init(void){
	
	struct task_struct *precess;
	
	struct task_struct *parent;
	
	struct task_struct *p;

	struct list_head *list;
	
    	printk("Precess Begin");
	
	printk("\tRelationShip\t\t\tcomm\t\t\tPID");

	for_each_process(p){			//根据pid找到进程的地址
		if(p->pid==pid){
			break;
		}
	}		
	parent = p->parent;			//找到进程的parent的地址

	printk("\tParent\t\t\t\t%s\t\t\t%d",parent->comm,parent->pid);
 
	list = &parent->children;			

	list_for_each(list,&parent->children){		//用list_for_each来遍历父进程的children即自己的sibling
		precess = list_entry(list,struct task_struct,sibling);
		printk("\tSibling\t\t\t\t%s\t\t\t%d",precess->comm,precess->pid);
	}

	list = &precess->children;
			
	list_for_each(list,&p->children){		//用list_for_each来遍历自己children
		precess = list_entry(list,struct task_struct,sibling);
		printk("\tChildren\t\t\t%s\t\t\t%d",precess->comm,precess->pid);
	}

	
	return 0;
}


static void dePreFa_exit(void){

    	printk(KERN_ALERT"Precess Out");
    
}

module_init(dePreFa_init);

module_exit(dePreFa_exit);

