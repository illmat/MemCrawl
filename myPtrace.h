#ifndef MYPTRACE_H_INCLUDED
#define MYPTRACE_H_INCLUDED

#include <sys/wait.h>
#include <sys/ptrace.h>
#include <errno.h>
#include <stdio.h>
#include <iostream>

int attach(pid_t);
int detach(pid_t);
int peek(pid_t, unsigned long, long&);
int poke(pid_t, unsigned long, long);

#endif // MYPTRACE_H_INCLUDED
