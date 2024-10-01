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

class Process {
public:
    virtual void monitor() = 0;                             // 监视功能需要在具体实现中定义
    virtual ~Process() = default;
};

class ExistingProcess : public Process {
public:
    explicit ExistingProcess(pid_t pid);                    // 构造函数
    void monitor() override;                                // 重写虚函数

private:
    pid_t pid;                                              // 要监视的进程号
};

class NewProcess : public Process {
public:
    explicit NewProcess(const std::string& processName);    // 构造函数
    void monitor() override;                                // 重写虚函数

private:
    void start();                                           // 启动新进程
    std::string processName;                                // 程序名称
    pid_t pid;                                              // 子进程的 PID
};

class ProcessMonitor {
public:
    explicit ProcessMonitor(std::shared_ptr<Process> proc); // 构造函数
    void run();                                             // 启动监视

private:
    std::shared_ptr<Process> process;                       // 监视的进程对象
};

// 参数解析函数声明
void parseArgs(int argc, char* argv[], std::shared_ptr<Process>& process);

#endif
