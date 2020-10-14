#ifndef GDBLITE_DEBUGGER_H
#define GDBLITE_DEBUGGER_H

#include <iostream>
#include <unordered_map>

#include "breakpoint.hpp"

class Debugger {
    private:
        std::string _prog_name; // Program being debugged
        pid_t _pid; // PID of the child process running the program
        std::unordered_map<std::intptr_t, Breakpoint> _breakpoints; // Map to keep track of set breakpoints

        bool validate_break_command(std::string& command) const;

    public:
        Debugger (std::string prog_name, pid_t pid);

        void run();

        void handle_input(std::string& line);

        void continue_execution();

        void set_breakpoint(std::intptr_t addr);
};

#endif