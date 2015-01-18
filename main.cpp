#include "myTypes.h"
#include "menu.h"
#include "maps.h"
#include "scan.h"
#include "print.h"

int main(int argc, char* argv[])
{
    pid_t pid;
    int input = 0;
    bool isFirstRun = true;
    std::string commando;
    std::vector<scanRegion> regions;
    std::vector<scanResult> results;

    if(argc < 2)
    {
        printError("usage ./MemCrawl <pid>");
        return 1;
    }

    if ((pid = atol(argv[1])) == 0)
    {
        printError("usage ./MemCrawl <pid>");
        return 1;
    }

    // get read/writeable scan regions
    if (getRegions(regions, pid) != 0)
    {
        printError("could not get regions");
        return 1;
    }

    std::cout << "Enter Command (try: help)" << std::endl;
    std::cout << results.size() << "> ";
    std::getline (std::cin, commando);

    while (commando != "quit" && commando != "q")
    {

        try
        {
            input = string2int(commando);
            if (isFirstRun)
            {
                isFirstRun = false;
                if (scanIntInit(regions, results, pid, input) != 0)
                {
                    printError("could not scan memory");
                    return 1;
                }
            }
            else
            {
                if (scanIntResults(results, pid, input) != 0)
                {
                    std::cout << "could not scan memory" << std::endl;
                    return 1;
                }
            }

        }
        catch (int e)
        {
            if (e == 1)
            {
                if (commando == "help")
                {
                    printHelp();
                }

                if (commando == "list")
                {
                    printResults(results);
                }

                if (commando == "update")
                {
                    if (updateIntResults(results, pid) != 0)
                    {
                        printError("could not scan memory");
                        return 1;
                    }
                }

                if (commando == "ulist")
                {
                    if (updateIntResults(results, pid) != 0)
                    {
                        printError("could not scan memory");
                        return 1;
                    }
                    printResults(results);
                }

                if (commando == "info")
                {
                    std::cout << std::endl << "scan regions: " << std::endl;
                    int adresses = 0;
                    for(std::vector<scanRegion>::iterator it = regions.begin(); it != regions.end(); ++it)
                    {
                        scanRegion sr = (scanRegion) *it;
                        std::cout << std::hex << sr.startRegion << " - " << sr.endRegion << std::dec <<std::endl;
                        adresses += sr.endRegion - sr.startRegion;
                    }
                    std::cout << std::endl << adresses << " adresses" << std::endl;

                }

                if (commando == "reset")
                {
                    regions.clear();
                    results.clear();
                    isFirstRun = true;
                    // get read/writeable scan regions
                    if (getRegions(regions, pid) != 0)
                    {
                        printError("could not get regions");
                        return 1;
                    }

                }

                if (commando.substr(0, 3) == "pid")
                {
                    if (commando.length() < 5)
                    {
                        std::cout << "correct usage: pid <pid>" << std::endl;
                    }
                    else
                    {
                        int val = 0;
                        std::stringstream ss(commando.substr(4, commando.length()));
                        if ((ss >> val).fail())
                        {
                            printError("wrong parameter for pid command");
                        }
                        else
                        {
                            pid = val;
                            // reset
                            regions.clear();
                            results.clear();
                            isFirstRun = true;
                            // get read/writeable scan regions
                            if (getRegions(regions, pid) != 0)
                            {
                                printError("could not get regions");
                                return 1;
                            }
                        }
                    }
                }

                if (commando.substr(0, 3) == "set")
                {
                    if (commando.length() < 5)
                    {
                        std::cout << "correct usage: set 5" << std::endl;
                    }
                    else
                    {
                        int val = 0;
                        std::stringstream ss(commando.substr(4, commando.length()));
                        if ((ss >> val).fail())
                        {
                            printError("wrong parameter for set command");
                        }
                        else
                        {
                            if (setInt(results, pid, val) != 0)
                            {
                                std::cout << "could not set value" << std::endl;
                                return 1;
                            }
                        }
                    }
                }
            }
            else
            {
                printError("unknown");
            }
        }
        std::cout << results.size() << "> ";
        std::getline (std::cin, commando);
    }

    return 0;
}

