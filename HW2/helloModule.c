#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/printk.h>
#include<linux/sched.h>
#include<linux/slab.h>
#include<linux/string.h>
#include<linux/vmalloc.h>

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

int proc_init (void) {
  printk(KERN_INFO "helloModule: kernel module initialized\n");

  
  getProcNum(pCountPtr, task);
  printk("%d", pCount);
  PID = kmalloc(sizeof(*PID) * pCount, GFP_KERNEL);
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
}

MODULE_LICENSE("GPL");
module_init(proc_init);
module_exit(proc_cleanup);

