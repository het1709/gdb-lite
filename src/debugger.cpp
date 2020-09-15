#include <iostream>
#include <sys/wait.h>
#include <sys/ptrace.h>

#include "debugger.h"
#include "linenoise.h"
#include "helpers.h"

Debugger::Debugger(std::string prog_name, pid_t pid)
    : _prog_name { std::move(prog_name) }, _pid { pid } {}

void Debugger::run() {
    // Wait until the child process (debugee program) has finished launching
    int wait_status;
    waitpid(_pid, &wait_status, 0);

    // Listen for user input
    char* line = nullptr;
    while ((line = linenoise("gdb-lite> ")) != nullptr) {
        handle_input(line);
        linenoiseHistoryAdd(line);
        linenoiseFree(line);
    }

}

void Debugger::handle_input(const std::string& line) {
    if (line == "") return;
    auto args = split(line, ' ');
    std::string command = args[0];

    if (is_prefix(command, "continue")) {
        continue_execution();
    } else {
        std::cerr << "Unknown command" << std::endl;
    }
}

void Debugger::continue_execution() {
    ptrace(PTRACE_CONT, _pid, nullptr, nullptr); // Continue the stopped traced process

    int wait_status;
    waitpid(_pid, &wait_status, 0);
}