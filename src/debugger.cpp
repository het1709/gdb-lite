#include <iostream>
#include <sys/wait.h>
#include <sys/ptrace.h>

#include "debugger.hpp"
#include "linenoise.h"
#include "helpers.hpp"

// 
// PUBLIC FUNCTIONS
// 

Debugger::Debugger(std::string prog_name, pid_t pid)
    : _prog_name{ std::move(prog_name) }, _pid{ pid } {}

void Debugger::run() {
    // Wait until the child process (debugee program) has finished launching
    int wait_status;
    waitpid(_pid, &wait_status, 0);

    // Listen for user input
    char* line = nullptr;
    while ((line = linenoise("gdb-lite> ")) != nullptr) {
        std::string cpp_line(line);
        to_lower(cpp_line);
        trim(cpp_line);
        handle_input(cpp_line);
        linenoiseHistoryAdd(line);
        linenoiseFree(line);
    }

}

void Debugger::handle_input(std::string& line) {
    if (line == "") return;
    auto args = split(line, ' ');
    std::string command = args[0];
    
    if (is_prefix(command, "continue")) {
        continue_execution();
    } else if (is_prefix(command, "break")) {
        if (validate_break_command(line)) {
            std::string addr{args[1], 2};
            set_breakpoint(std::stol(addr, 0, 16));
        } else {
            std::cerr << "Invalid break command" << std::endl;
            std::cerr << "Format:" << std::endl;
            std::cerr << "break 0xADDRESS" << std::endl;
        };
    } else {
        std::cerr << "Unknown command" << std::endl;
    }
}

void Debugger::continue_execution() {
    ptrace(PTRACE_CONT, _pid, nullptr, nullptr); // Continue the stopped child process

    int wait_status;
    waitpid(_pid, &wait_status, 0);
}

void Debugger::set_breakpoint(std::intptr_t addr) {
    Breakpoint bp{_pid, addr};
    bp.enable();
    _breakpoints[addr] = bp;
    std::cout << "Breakpoint at address 0x" << std::hex << addr << " set" << std::endl;
}

// 
// PRIVATE FUNCTIONS
// 

bool Debugger::validate_break_command(std::string& command) const {
    auto parts = split(command, ' ');
    if (parts.size() != 2) { return false; }
    std::string address = parts[1];

    return address.compare(0, 2, "0x") == 0
        && address.size() > 2
        && address.find_first_not_of("01234567890abcdef", 2) == std::string::npos;

}