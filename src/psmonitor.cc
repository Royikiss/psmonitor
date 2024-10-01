#include "../include/psmonitor.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdexcept>
#include <cstring>

// ExistingProcess 类的构造函数实现
ExistingProcess::ExistingProcess(pid_t pid) : pid(pid) {}

// ExistingProcess 类的 monitor 实现
void ExistingProcess::monitor() {
    std::cout << "Monitoring existing process: " << pid << std::endl;
    while (true) {
        if (kill(pid, 0) == -1) {
            std::cout << "Process " << pid << " has stopped. Exiting...\n";
            break;
        }
        sleep(2); // 间隔 2 秒检查一次
    }
}

// NewProcess 类的构造函数实现
NewProcess::NewProcess(const std::string& processName) : processName(processName), pid(-1) {}

// NewProcess 类的 start 函数实现
void NewProcess::start() {
    pid = fork();
    if (pid == 0) {
        execlp(processName.c_str(), processName.c_str(), nullptr);
        std::cerr << "Failed to start process: " << processName << "\n";
        exit(1);
    }
}

// NewProcess 类的 monitor 函数实现
void NewProcess::monitor() {
    while (true) {
        if (pid == -1 || waitpid(pid, nullptr, 0) > 0) {
            std::cout << "Process stopped. Restarting...\n";
            start(); // 如果进程停止，重新启动
        }
    }
}

// ProcessMonitor 类的构造函数实现
ProcessMonitor::ProcessMonitor(std::shared_ptr<Process> proc) : process(std::move(proc)) {}

// ProcessMonitor 类的 run 函数实现
void ProcessMonitor::run() {
    process->monitor();
}

// 参数解析函数实现
void parseArgs(int argc, char* argv[], std::shared_ptr<Process>& process) {
    if (argc < 3) {
        throw std::invalid_argument("Usage: -p <pid> or -n <process_name>");
    }

    if (std::strcmp(argv[1], "-p") == 0) {
        pid_t pid = std::stoi(argv[2]);
        process = std::make_shared<ExistingProcess>(pid);
    } else if (std::strcmp(argv[1], "-n") == 0) {
        std::string processName = argv[2];
        process = std::make_shared<NewProcess>(processName);
    } else {
        throw std::invalid_argument("Invalid option. Use -p for existing process or -n for new process.");
    }
}
