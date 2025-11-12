#include "types.h"
#include "param.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "defs.h"
#include "alarm.h"


int sigalarm(void) {
    struct proc* p = myproc();
    if (p->interval == 0) {
        return 0;
    }
    p->left_ticks--;
    if (p->left_ticks == 0 && p->handler_exec == 0) {
        memmove(p->trapframe_backup, p->trapframe, sizeof(struct trapframe));
        p->trapframe->epc = p->handler;
        p->handler_exec = 1;
    }
    return 0;
}

int sigreturn(void) {
    struct proc* p = myproc();
    p->left_ticks = p->interval;
    memmove(p->trapframe, p->trapframe_backup, sizeof(struct trapframe));
    p->handler_exec = 0;
    return p->trapframe->a0;
}