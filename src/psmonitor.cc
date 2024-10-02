#include "../include/psmonitor.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdexcept>
#include <cstring>

// ExistingProcess 实现
ExistingProcess::ExistingProcess(pid_t pid) : pid(pid) {}

void ExistingProcess::monitor(int sleep_time = 2) {
    std::cout << "Monitoring existing process: " << pid << std::endl;
    while (true) {
        if (kill(pid, 0) == -1) {
            std::cout << "Process " << pid << " has stopped. Exiting...\n";
            break;
        }
        sleep(sleep_time);
    }
}

// NewProcess 实现
NewProcess::NewProcess(const std::string& processName) : processName(processName), pid(-1) {}

void NewProcess::start() {
    pid = fork();
    if (pid == 0) {
        execlp(processName.c_str(), processName.c_str(), nullptr);
        std::cerr << "Failed to start process: " << processName << "\n";
        exit(1);
    }
}

void NewProcess::monitor(int sleep_time = 2) {
    while (true) {
        if (pid == -1 || waitpid(pid, nullptr, 0) > 0) {
            std::cout << "Process stopped. Restarting...\n";
            start(); // 如果进程停止，重新启动
        }
        sleep(sleep_time);
    }
}

// ProcessMonitor 实现
ProcessMonitor::ProcessMonitor(std::shared_ptr<Process> proc) : process(std::move(proc)) {}

void ProcessMonitor::startmonitor() {
    process->monitor();
}

// TaskOrganizer 实现
TaskOrganizer::TaskOrganizer() = default;

bool TaskOrganizer::isOptionSeen(const std::string& option) const {
    return this->seenOptions.find(option) != this->seenOptions.end();
}

void TaskOrganizer::addOption(const std::string &option, const std::string &value) {
    if (isOptionSeen(option)) {
        throw std::invalid_argument("Option " + option + " has already been provided.");
    } else {
        seenOptions.insert(option);
        options[option] = value;
    }
    return ;
}

void TaskOrganizer::validateOptions() const {
    if (isOptionSeen("e") && isOptionSeen("n")) {
        throw std::invalid_argument("Options -e and -n cannot be used together.");
    }
    if (!isOptionSeen("e") && !isOptionSeen("n")) {
        throw std::invalid_argument("Please enter the pid of an existing process or the path of a new process");
    }
    return ;
}

std::unordered_map<std::string, std::string> TaskOrganizer::getmap() const {
    return this->options;
}

void _parseArgs(int argc, char *argv[], TaskOrganizer &organizer) {
    char ch;
    if (argc < 3) {
        throw std::invalid_argument("Usage: -p <pid> or -n <process_name>");
    }

    // e: Existing process
    // n: New process
    // b: Behavior
    while ((ch = getopt(argc, argv, "e:n:b:")) != -1) {
        switch (ch) {
            case 'e': {
                            organizer.addOption("e", optarg);
                      }; break;
            case 'n': {
                            organizer.addOption("n", optarg);
                      }; break;
            case 'b': {
                            organizer.addOption("b", optarg);
                      }; break;
            default: {
                         throw std::invalid_argument("Invalid option. Use -p for existing process or -n for new process.");
                     };
        }
    }
    organizer.validateOptions();
    return ;
}

void taskGeneration(std::shared_ptr<Process> &process, TaskOrganizer &organizer) {
    if (organizer.getmap().count("e") > 0) {
        pid_t pid = std::stoi(organizer.getmap()["e"]);
        process = std::make_shared<ExistingProcess>(pid);
    } else {
        std::string processName = organizer.getmap()["n"];
        process = std::make_shared<NewProcess>(processName);
    }
    return ;
}

// 参数解析函数实现
void parseArgs(int argc, char* argv[], std::shared_ptr<Process> &process) {

    TaskOrganizer organizer;
    
    _parseArgs(argc, argv, std::ref(organizer));

    taskGeneration(process, organizer);

    return ;
}
