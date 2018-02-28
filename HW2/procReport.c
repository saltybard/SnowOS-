#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/printk.h>
#include<linux/sched.h>
#include<linux/slab.h>
#include<linux/string.h>
#include<linux/vmalloc.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

void getProcNum(int* pC, struct task_struct* task);
void genProcReport(void);

struct task_struct* task;
struct task_struct* child;
struct list_head* childList;
int runnable = 0;
int unrunnable = 0;
int stopped = 0;
int childCount = 0;
int pCount = 0;
int* pCountPtr = &pCount;
int* PID;
int* cPID;
int* numChild;
char** procName;
char** childName;
char* const CHILD_STRING = "*No Children";
int stats[3];

#define n_array (sizeof (array) / sizeof (const char *))

static int procReport_show(struct seq_file *m, void *v) {
  int i;  
  seq_printf(m, "PROCESS REPORTER:\n");
  seq_printf(m, "Unrunnable: %d\nRunnable: %d\nStopped: %d\n", stats[0], stats[1], stats[2]);

	for (i = 0; i < pCount; i++) { 
		//seq_printf(m, "%d: %s\n", i, array[i]);
		if (numChild[i] == 0) { 
			seq_printf(m, "Process ID=%d Name=%s *No Children\n", PID[i], procName[i]);
		} else { 
			seq_printf(m, "Process ID=%d Name=%s number_of_children=%d first_child_pid=%d first_child_name=%s\n", PID[i], procName[i], numChild[i], cPID[i], childName[i]);
		}
	}

  return 0;
}

static int procReport_open(struct inode *inode, struct  file *file) {
  return single_open(file, procReport_show, NULL);
}

static const struct file_operations procReport_fops = {
  .owner = THIS_MODULE,
  .open = procReport_open,
  .read = seq_read,
  .llseek = seq_lseek,
  .release = single_release,
};

int proc_init (void) {
  printk(KERN_INFO "helloModule: kernel module initialized\n");

  
  getProcNum(pCountPtr, task);
  printk("%d", pCount);
  PID = kmalloc(sizeof(*PID) * pCount, GFP_KERNEL);
	//printk("%d", sizeof(*PID) * pCount);
  cPID = kmalloc(sizeof(*cPID) * pCount, GFP_KERNEL);
  numChild = kmalloc(sizeof(*numChild) * pCount, GFP_KERNEL);
  procName = vmalloc(sizeof(char*) * pCount);
  childName = vmalloc(sizeof(char*) * pCount);
  genProcReport();
  //printk("TestChildName: %s", childName[2]);
  stats[0] = unrunnable;
  stats[1] = runnable;
  stats[2] = stopped;

  //printk("test: %s", procName[0]);

  
  printk("PROCESS REPORTER:\n");
  printk("Unrunnable: %d\nRunnable: %d\nStopped: %d\n", unrunnable, runnable, stopped);

  proc_create("proc_report", 0, NULL, &procReport_fops);
  return 0;
}

void getProcNum(int* pC, struct task_struct* task) {
  for_each_process(task) {
    (*pC)++;
  }
}


void genProcReport() {
  int i = 0;
  for_each_process(task) { 
    childCount = 0; 
    //printk("%s[%d]\n", task->comm, task->pid);
    PID[i] = task->pid;
    procName[i] = (char*)vmalloc(strlen(task->comm) + 1);
    procName[i] = task->comm;

    if (task->state == -1) unrunnable++; 
    if (task->state == 0) runnable++; 
    if (task->state > 0) stopped++;
    
    list_for_each(childList, &task->children) { 
      child = list_entry(childList, struct task_struct, sibling);
      if (childCount == 0){
	cPID[i] = child->pid;
	childName[i] = (char*)vmalloc(strlen(child->comm) + 1);
	childName[i] = child->comm;
      } 
      childCount++; 
    }
    //if (childCount > 0) printk("Child: %s (%d)", childName, childCount);
    if (childCount == 0) {
      childName[i] = (char*)vmalloc(strlen(CHILD_STRING) + 1);
      childName[i] = CHILD_STRING;
      cPID[i] = 0;
    }
    numChild[i] = childCount;
    i++;
   } 
}

void proc_cleanup(void) {
  printk(KERN_INFO "helloModule: performing cleanup of module\n");
  remove_proc_entry("proc_report", NULL);
}

/*static int __init procReport_init(void) {
  proc_create("procReport", 0, NULL, &procReport_fops);
  return 0;
}*/

/*static void __exit procReport_exit(void) {
  remove_proc_entry("proc_Report", NULL);
}*/


MODULE_LICENSE("GPL");
module_init(proc_init);
module_exit(proc_cleanup);

