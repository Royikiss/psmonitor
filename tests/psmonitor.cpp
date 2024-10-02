/*************************************************************************
	> File Name: psmonitor.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 01 Oct 2024 04:14:45 PM CST
 ************************************************************************/

#include "../include/psmonitor.h"
#include <iostream>
#include <memory>

int main(int argc, char* argv[]) {
    try {
        std::shared_ptr<Process> process;
        parseArgs(argc, argv, process);

        ProcessMonitor monitor(process);
        monitor.startmonitor(); // 开始监视
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

