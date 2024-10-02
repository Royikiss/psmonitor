/*************************************************************************
	> File Name: psmonitor.h
	> Author: 
	> Mail: 
	> Created Time: Tue 01 Oct 2024 04:16:21 PM CST
 ************************************************************************/

#ifndef _PSMONITOR_H
#define _PSMONITOR_H

#include <memory>
#include <string>
#include <unordered_map>
#include <set>

class Process {
public:
    virtual void monitor(int sleep_time = 2) = 0; 
    virtual ~Process() = default;
};

class ExistingProcess : public Process {
public:
    explicit ExistingProcess(pid_t pid);                    // 构造函数
    void monitor(int) override;                                // 重写虚函数

private:
    pid_t pid;                                              // 要监视的进程号
};

class NewProcess : public Process {
public:
    explicit NewProcess(const std::string& processName);    // 构造函数
    void monitor(int) override;                                // 重写虚函数

private:
    void start();                                           // 启动新进程
    std::string processName;                                // 程序名称
    pid_t pid;                                              // 子进程的 PID
};

class ProcessMonitor {
public:
    explicit ProcessMonitor(std::shared_ptr<Process> proc);
    void startmonitor(); 

private:
    std::shared_ptr<Process> process; 
};

class TaskOrganizer {
public:
    TaskOrganizer();
    void addOption(const std::string &option, const std::string &value);
    bool isOptionSeen(const std::string &option) const ;
    void validateOptions() const;
    std::unordered_map<std::string, std::string> getmap() const ;
private:
    std::set<std::string> seenOptions;
    std::unordered_map<std::string, std::string> options;
};

enum Behavior {
    RESTART
};

void _parseArgs(int argc, char *argv[], TaskOrganizer &organizer); 

void taskGeneration(std::shared_ptr<Process> &process, TaskOrganizer &organizer);

void parseArgs(int argc, char* argv[], std::shared_ptr<Process>& process);

#endif
