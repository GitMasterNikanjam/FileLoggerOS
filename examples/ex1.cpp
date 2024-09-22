// For compile and build:
// g++ -std=c++17 -o main main.cpp FileLogger.cpp
// ###############################################################

#include "FileLogger.h"
#include <iostream>

FileLogger logger;

int main() 
{
    logger.setDir("./folder1");
    if(!logger.open("test1.txt",FILE_WRITE))
        printf("can not open.\n");

    if(logger.exists("test1.txt"))
        printf("exist\n");

    // Close the file
    logger.close();

    return 0;
}

