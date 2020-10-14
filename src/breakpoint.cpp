#include <sys/ptrace.h>

#include "breakpoint.hpp"

Breakpoint::Breakpoint() = default;
Breakpoint::Breakpoint(pid_t pid, std::intptr_t addr)
    : _pid{ pid }, _addr{ addr }, _enabled{ false }, _saved_instr{} {}

bool Breakpoint::is_enabled() const { return _enabled; }
bool Breakpoint::get_address() const { return _addr; }

/**
 * To enable a breakpoint at the given _addr we must replace the instruction at _addr
 * with the assembly instruction INT 3. When INT 3 gets executed, control is passed to
 * the debug interrupt handler which sends a SIGTRAP signal to the program being debugged.
*/
void Breakpoint::enable() {
    auto word = ptrace(PTRACE_PEEKDATA, _pid, _addr, nullptr); // Returns the 64 bits (word) of data present at _addr
    
    _saved_instr = static_cast<uint8_t>(word & 0xFF); // Save the lower byte
    uint64_t INT3 = 0xCC; // The opcode for the INT 3 instruction
    uint64_t updated_word = (word & 0x00) | INT3; // Set the lower byte to INT 3

    ptrace(PTRACE_POKEDATA, _pid, _addr, updated_word); // Copy updated_instr to _addr

    _enabled = true;
}


/**
 * To disable a breakpoint we just need to replace the INT 3 instruction with the _saved_instr
*/
void Breakpoint::disable() {
    auto word = ptrace(PTRACE_PEEKDATA, _pid, _addr, nullptr);
    uint64_t updated_word = (word & 0x00) | _saved_instr;

    ptrace(PTRACE_POKEDATA, _pid, _addr, updated_word);

    _enabled = false;
}