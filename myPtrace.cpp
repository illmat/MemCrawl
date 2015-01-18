#include "myPtrace.h"

// attach to pid
int attach(pid_t pid)
{
    int status;
    if(ptrace(PTRACE_ATTACH, pid, NULL, NULL))
    {
        perror("PTRACE_ATTACH");
        return 1;
    }
    else
    {
        std::cout << "attached to " << pid << std::endl << "wait for child" << std::endl;
        wait(&status);
        std::cout << "Status: " << status << std::endl;
    }
    return 0;
}


// detach to pid
int detach(pid_t pid)
{
    if(ptrace(PTRACE_DETACH, pid, NULL, NULL))
    {
        perror("PTRACE_DETACH");
        return 1;
    }
    else
    {
        std::cout << "detached from " << pid << std::endl;
    }
    return 0;
}


// peek data
int peek(pid_t pid, unsigned long addr, long &buffer)
{
    errno = 0;
    if(((buffer = ptrace(PTRACE_PEEKDATA, pid, (void *)addr, NULL)) == -1) && errno)
    {
        perror("PTRACE_PEEKDATA");
        if(ptrace(PTRACE_DETACH, pid, NULL, NULL))
            perror("PTRACE_DETACH");
        return 1;
    }
    else
    {
        //std::cout << "peeked " << buffer << std::endl;
    }
    return 0;
}


// poke data
int poke(pid_t pid, unsigned long addr, long buffer)
{
    errno = 0;
    if (ptrace(PTRACE_POKEDATA, pid, (void *)addr, buffer) == -1 && errno)
    {
        perror("PTRACE_POKE");
        return 1;
    }
    else
    {
        std::cout << "successfully wrote " << buffer << " to " << std::hex << "0x" << addr << std::dec << std::endl;
    }
    return 0;
}
