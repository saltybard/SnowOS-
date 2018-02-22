#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/printk.h>
#include<linux/sched.h>

int proc_init (void) {
  struct task_struct* task;
  struct task_struct* child;
  struct list_head* childList;
  int runnable = 0;
  int unrunnable = 0;
  int stopped = 0;
  int childCount = 0;
  char* childName;
  printk(KERN_INFO "helloModule: kernel module initialized\n");

  for_each_process(task) {
    childCount = 0;
    printk("%s[%d]\n", task->comm, task->pid);
    if (task->state == -1) unrunnable++;
    if (task->state == 0) runnable++;
    if (task->state > 0) stopped++;
    list_for_each(childList, &task->children) {
      child = list_entry(childList, struct task_struct, sibling);
      if (childCount == 0){
	//printk("Child: %s", child->comm);
	childName = child->comm;
      }
      childCount++;
    }
    if (childCount > 0) printk("Child: %s (%d)", childName, childCount);
  }
  printk("PROCESS REPORTER:\n");
  printk("Unrunnable: %d\nRunnable: %d\nStopped: %d\n", unrunnable, runnable, stopped);
  return 0;
}

void proc_cleanup(void) {
  printk(KERN_INFO "helloModule: performing cleanup of module\n");
}

MODULE_LICENSE("GPL");
module_init(proc_init);
module_exit(proc_cleanup);

