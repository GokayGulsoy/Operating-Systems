/*
Group Number: G18
Student number: 270201071 Merve Nur Ozan
Student number: 270201072 Gökay Gülsoy
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>
#include <linux/dcache.h>
#include <linux/mm.h>
#include <linux/sched/signal.h>
#include <linux/seq_file.h>
#include <linux/path.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Merve Nur Ozan and Gökay Gülsoy");
MODULE_DESCRIPTION("Kernel module that displays information related to a process according to its ID or name");
MODULE_VERSION("0.1");

static unsigned int upid = 0;
static char *upname = "";

module_param(upid, int, 0);
MODULE_PARM_DESC(upid, "Process ID");
module_param(upname, charp, 0);
MODULE_PARM_DESC(upname, "Process name");

static struct task_struct *task;
static struct mm_struct *mm;
static char process_path[PATH_MAX];

static int display_proc_info(struct seq_file *m, void *v) {
    if (upid != 0) {
        task = pid_task(find_vpid(upid), PIDTYPE_PID);
        if (task == NULL) {
            pr_err("Error: Process with ID %d not found\n", upid);
            return 2;
        }
    } else if (strcmp(upname, "") != 0) {
        for_each_process(task) {
            if (strcmp(task->comm, upname) == 0) {
                break;
            }
        }

        if (strcmp(task->comm, upname) != 0) {
            pr_err("Error: Process with name %s not found\n", upname);
            return 2;
        }
    } else {
        pr_err("Error: Either correct process ID or name must be provided!\n");
        return 2;
    }

    seq_printf(m, "Name: %s\n", task->comm);
    seq_printf(m, "PID: %d\n", task->pid);
    seq_printf(m, "PPID: %d\n", task->real_parent->pid);
    seq_printf(m, "UID: %d\n", task->cred->uid.val);

    mm = task->mm;
    if (mm) {
        struct file *executable = mm->exe_file;
        if (executable) {
            char *full_path = d_path(&executable->f_path, process_path, PATH_MAX);
            if (IS_ERR(full_path)) {
                seq_printf(m, "Path: Error occured while resolving path!\n");
            } else {
                seq_printf(m, "Path: %s\n", full_path);
            }
        } else {
            seq_printf(m, "Path: Error occured while resolving path!\n");
        }
    } else {
        seq_printf(m, "Path: Error occured while resolving path!\n");
    }

    seq_printf(m, "State: %d\n", task_state_index(task));

    if (task_state_index(task) == TASK_INTERRUPTIBLE) {
        unsigned long rss = get_mm_rss(task->mm);
        seq_printf(m, "Memory Usage: %lu KB\n", rss * PAGE_SIZE / 1024);
    } else {
        seq_printf(m, "Memory Usage: None (Process is not running)\n");
    }

    return 0;
}

static int procinfo_open(struct inode *inode, struct file *file) {
    return single_open(file, display_proc_info, NULL);
}

static const struct proc_ops proc_info_fops = {
    .proc_open = procinfo_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init proc_info_init(void) {
    // creating a proc file
    proc_create("proc_info_module", 0666, NULL, &proc_info_fops);
    return 0;
}

static void __exit proc_info_exit(void) {
    // removing the proc file
    remove_proc_entry("proc_info_module", NULL);
}

module_init(proc_info_init);
module_exit(proc_info_exit);

