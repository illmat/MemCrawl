#ifndef SCANINT_H_INCLUDED
#define SCANINT_H_INCLUDED

#include <vector>
#include "myPtrace.h"
#include "myTypes.h"

int scanIntInit(std::vector<scanRegion> , std::vector<scanResult> &, pid_t, int);
int scanIntResults(std::vector<scanResult> &, pid_t, int);
int setInt(std::vector<scanResult> &, pid_t, int);
int updateIntResults(std::vector<scanResult> &, pid_t);

#endif // SCANINT_H_INCLUDED
