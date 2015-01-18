#include "scan.h"

// initial scan, get all relevant regions from /proc/<pid>/maps
int scanIntInit(std::vector<scanRegion> regions, std::vector<scanResult> &results, pid_t pid, int scanValue)
{
    unsigned long startAddr = 0, endAddr = 0;
    long buffer = 0;

    if (attach(pid) != 0)
    {
        return 1;
    }
    else
    {
        for (unsigned int x=0; x<regions.size(); x++)
        {
            scanResult result;
            startAddr = regions[x].startRegion;
            endAddr = regions[x].endRegion;

            while (startAddr < endAddr)
            {

                if (peek(pid, startAddr, buffer) != 0)
                {
                    return 1;
                }
                if (buffer == scanValue)
                {
                    result.addr = startAddr;
                    result.value = buffer;
                    results.push_back(result);
                }
                startAddr += sizeof(unsigned long);

            }

        }

    }

    detach(pid);
    return 0;
}


// scan a set of results
int scanIntResults(std::vector<scanResult> &results, pid_t pid, int scanValue)
{
    long buffer = 0;
    scanResult result;
    std::vector<scanResult> newResults;

    if (attach(pid) != 0)
    {
        return 1;
    }
    else
    {
        for (unsigned int x=0; x<results.size(); x++)
        {
            if (peek(pid, results[x].addr, buffer) != 0)
            {
                return 1;
            }
            if (buffer == scanValue)
            {
                result.addr = results[x].addr;
                result.value = buffer;
                newResults.push_back(result);
            }

        }

    }
    results = newResults;
    detach(pid);

    return 0;
}


// update results
int updateIntResults(std::vector<scanResult> &results, pid_t pid)
{
    long buffer = 0;

    if (attach(pid) != 0)
    {
        return 1;
    }
    else
    {
        for (unsigned int x=0; x<results.size(); x++)
        {
            if (peek(pid, results[x].addr, buffer) != 0)
            {
                return 1;
            }
            else {
                results[x].value = buffer;
            }
        }

    }
    detach(pid);

    return 0;
}

// set all results to value
int setInt(std::vector<scanResult> &results, pid_t pid, int value)
{
    if (attach(pid) != 0)
    {
        return 1;
    }
    else
    {
        for (unsigned int x=0; x<results.size(); x++)
        {
            if (poke(pid, results[x].addr, value) != 0)
            {
                return 1;
            }
        }
    }

    detach(pid);

    return 0;
}
