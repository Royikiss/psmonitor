# Process Monitor Program

## Overview

This is a C++ program that monitors a specific process by either:
1. Monitoring an already running process given its PID (`-p` option).
2. Starting a new process and monitoring it (`-n` option).

When the monitored process stops, the program will attempt to restart it if it was started with the `-n` option.

## Features

- **Process monitoring**: Keep track of an existing process or start and monitor a new process.
- **Automatic restart**: If a new process is started with the `-n` option and stops unexpectedly, the program will restart it.

## Build Instructions

This project uses CMake to manage the build process.

### Steps:

1. Clone the repository:
    ```bash
    git clone https://github.com/Royikiss/psmonitor.git
    cd psmonitor
    ```

2. Create a build directory and run CMake:
    ```bash
    mkdir build
    cd build
    cmake ..
    ```

3. Build the program:
    ```bash
    make
    ```

After building, an executable named `psmonitor` will be created in the `build` directory.

## Usage

To use this program, you can either monitor an existing process by its PID or start a new one to monitor.

### Monitor an existing process:
```bash
./psmonitor -p <pid>
```
For example, to monitor a process with PID 1234:
```bash
./psmonitor -p 1234
```

### Start and monitor a new process:
```bash
./psmonitor -n <process_name>
```
For example, to start and monitor a process named `my_program`:
```bash
./psmonitor -n my_program
```

### Available options:

- `-p <pid>`: Monitor an existing process with the given PID.
- `-n <process_name>`: Start a new process and monitor it.

## Example

1. Monitor an existing process with PID 4321:
   ```bash
   ./psmonitor -p 4321
   ```

2. Start and monitor a new process `myapp`:
   ```bash
   ./psmonitor -n myapp
   ```

## Dependencies

- **CMake**: A tool to manage the build process.
- **g++**: GNU C++ compiler.
