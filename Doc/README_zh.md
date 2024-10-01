# 进程监视程序

## 概述

这是一个 C++ 程序，用于监视特定的进程，功能如下：
1. 通过提供的进程号 (PID) 监视已在运行的进程（使用 `-p` 选项）。
2. 启动一个新进程并对其进行监视（使用 `-n` 选项）。

当被监视的进程停止时，如果是通过 `-n` 选项启动的进程，程序将尝试重新启动它。

## 功能特点

- **进程监视**: 监视已存在的进程或启动并监视一个新进程。
- **自动重启**: 如果通过 `-n` 选项启动的新进程意外停止，程序将重新启动该进程。

## 构建步骤

本项目使用 CMake 来管理构建过程。

### 步骤：

1. 克隆代码仓库：
    ```bash
    git clone https://github.com/Royikiss/psmonitor.git
    cd psmonitor
    ```

2. 创建构建目录并运行 CMake：
    ```bash
    mkdir build
    cd build
    cmake ..
    ```

3. 编译程序：
    ```bash
    make
    ```

编译完成后，将在 `build` 目录中生成名为 `psmonitor` 的可执行文件。

## 使用方法

你可以通过进程号监视已存在的进程，或启动一个新进程并进行监视。

### 监视已有进程：
```bash
./psmonitor -p <pid>
```
例如，监视 PID 为 1234 的进程：
```bash
./psmonitor -p 1234
```

### 启动并监视新进程：
```bash
./psmonitor -n <process_name>
```
例如，启动并监视名为 `my_program` 的进程：
```bash
./psmonitor -n my_program
```

### 可用选项：

- `-p <pid>`: 通过给定的进程号监视已存在的进程。
- `-n <process_name>`: 启动一个新进程并监视它。

## 示例

1. 监视已有的进程（进程号 4321）:
   ```bash
   ./psmonitor -p 4321
   ```

2. 启动并监视一个名为 `myapp` 的新进程:
   ```bash
   ./psmonitor -n myapp
   ```

## 依赖项

- **CMake**: 用于管理构建过程的工具。
- **g++**: GNU C++ 编译器。

