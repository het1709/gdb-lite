# What is gdb-lite?
`gdb-lite` is a custom (and simplified) "gdb-like" debugger written in C++ for Linux. This is an ongoing project to help me learn more about C++ language features, how a debugger actually works, and some intricacies of Linux. In doing so I also hope to gain a better understanding on how to build readable and highly performant C++ software.

Shoutout to Simon Brand for his exceptional series of blog posts on Linux Debuggers which can be found here: https://blog.tartanllama.xyz/writing-a-linux-debugger-setup/ . Most of the code in this project will be adapted from his blog posts.

# What features will gdb-lite support?
All basic features of a debugger will be supported such as:
- Launch, halt, and continue execution
- Breakpoints on
    - memory addresses
    - source code lines
    - function entries
- Read and write registers and memory
- Single stepping
    - step in
    - step out
    - step over
- Print current source location
- Print backtrace
- Print values of variables

Additionally, I will try my hand at some more advanced features as well, such as:
- Remote debugging
- Shared library and dynamic-loading support 
- Expression evaluation
- Multi-threaded debugging