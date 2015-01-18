#include "maps.h"

int getRegions(std::vector<scanRegion> &regions, pid_t pid)
{
    std::stringstream path;
    path << "/proc/" << pid << "/maps";
    std::cout << "path:" << path.str() << std::endl;
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(path.str().c_str(), "r");
    if (fp == NULL)
    {
        std::cout << "unable to open file" << std::endl;
        return 1;
    }

    scanRegion lineBuffer;
    char readable, writeable;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (sscanf(line, "%lx-%lx %c%c", &lineBuffer.startRegion, &lineBuffer.endRegion, &readable, &writeable) >= 4)
        {
            if ((readable == 'r') && (writeable == 'w'))
            {
                regions.push_back(lineBuffer);
            }
        }

    }
    fclose(fp);
    free(line);
    return 0;
}

