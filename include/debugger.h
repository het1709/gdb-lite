#include <iostream>

class Debugger {
    public:
        Debugger (std::string prog_name, pid_t pid);

        void run();

        void handle_input(const std::string& line);

        void continue_execution();

    private:
        std::string _prog_name;
        pid_t _pid;
};