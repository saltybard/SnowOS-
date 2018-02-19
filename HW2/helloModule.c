#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/printk.h>
#include<linux/sched.h>

int proc_init (void) {
  struct task_struct *task;
  printk(KERN_INFO "helloModule: kernel module initialized\n");

  for_each_process(task) {
    printk("%s[%d]\n", task->comm, task->pid);
  }
  return 0;
}

void proc_cleanup(void) {
  printk(KERN_INFO "helloModule: performing cleanup of module\n");
}

MODULE_LICENSE("GPL");
module_init(proc_init);
module_exit(proc_cleanup);

