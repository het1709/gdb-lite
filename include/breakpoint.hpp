#ifndef GDBLITE_BREAKPOINT_H
#define GDBLITE_BREAKPOINT_H

#include <cstdint>
#include <sys/types.h>

class Breakpoint {
    private:
        pid_t _pid;
        std::intptr_t _addr;
        bool _enabled;
        uint8_t _saved_instr; // data which used to be at the breakpoint address
                              // and got replaced with the INT 3 instruction

    public:
        Breakpoint();
        Breakpoint(pid_t pid, std::intptr_t addr);

        void enable();
        void disable();

        bool is_enabled() const;
        bool get_address() const;
};

#endif