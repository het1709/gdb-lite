#include <iostream>
#include <unistd.h>
#include <sys/ptrace.h>
#include <errno.h>
#include <string.h>

#include "debugger.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Please specify a program to debug" << std::endl;
        return -1;
    }    
    auto program = argv[1];
    auto pid = fork();

    if (pid == 0) {
        // we're in the newly created child process
        // execute debugee (program)
        errno = 0; // reset errno since ptrace() sets errno in case of error

        // allow the parent process to observe and control the execution of the child process
        ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);
        if (errno != 0) {
            int error = errno; // cache errno into a variable in case some other program resets it before it can be outputted
            std::cerr << "ptrace() ran into an error" << std::endl;
            std::cerr << strerror(error) << std::endl;
            return -1;
        }
        execl(program, program, nullptr); // Execute the debugee program with no arguments
    } else if (pid > 0) {
        // we're in the parent process
        // execute debugger
        Debugger dbg{program, pid};
        dbg.run();
    } else {
        std::cerr << "Could not create child process" << std::endl;
        return -1;
    }
}