#include "print.h"

void printResults(std::vector<scanResult> results)
{
    for (unsigned i=0; i<results.size(); i++)
    {
        std::cout << std::dec << "[" << i << "] = " <<"0x" << std::hex << results[i].addr << std::dec << " contains: " << results[i].value << std::endl;
    }
}

void printError(std::string errorMsg) {
    std::cout << "Error: " << errorMsg << std::endl;
}

void printHelp() {
    std::cout << "MemCrawl options: " << std::endl;
    std::cout << "help:\t\tprints this help screen" << std::endl;
    std::cout << "list:\t\tprints a list of all entries" << std::endl;
    std::cout << "update:\t\tupdates all entries" << std::endl;
    std::cout << "ulist:\t\tupdates and lists all entries" << std::endl;
    std::cout << "info:\t\tprints info about scan regions" << std::endl;
    std::cout << "set <number>:\tsets all entries to <number>" << std::endl;
    std::cout << "reset:\t\tresets all entries" << std::endl;
    std::cout << "pid:\t\tchange to pid" << std::endl;

}
