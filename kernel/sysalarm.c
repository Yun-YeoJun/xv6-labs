#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "alarm.h"

uint64 sys_sigalarm() {
    int interval;
    void (*handler)();

    argint(0,&interval);
    argaddr(1, (uint64*)&handler);

    struct proc* p = myproc();
    p->interval = p->left_ticks = interval;
    p->handler = (uint64)handler;

    return 0;
}
uint64 sys_sigreturn() {
    return sigreturn();
}