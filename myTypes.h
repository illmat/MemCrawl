#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

struct scanRegion
{
    unsigned long startRegion;
    unsigned long endRegion;
};

struct scanResult
{
    unsigned long addr;
    int value;
};

enum command
{
    HELP,
    PID,
    QUIT,
    RESET
};
#endif // TYPES_H_INCLUDED
