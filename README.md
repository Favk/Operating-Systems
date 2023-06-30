# Operating-Systems
This is all the assignments and code I have worked on in my operating systems classes

Assignment 1: Mav shell (msh)
# msh.c - Shell Program Summary

This project involves the creation of a shell program called Mav shell (msh), similar to other popular shell programs like bash, csh, or ksh. The shell accepts commands, forks child processes, and executes those commands. The program runs continuously until the user exits the shell.

Functional Requirements:
1. The program displays the prompt "msh>" and reads a line of input. If the command is supported, it executes the command and displays the output.
2. If an unsupported command is entered, the shell prints "invalid command: Command not found."
4. After each command completes, the program prints the "msh>" prompt and waits for another line of input.
5. The shell exits with a status of zero if the command is "quit" or "exit".
6. If the user enters a blank line, the shell prints another prompt and waits for input.
7. The shell supports up to 10 command line parameters in addition to the command.
8. It executes any valid command in the following paths: current working directory, /usr/local/bin, /usr/bin, and /bin.
9. The shell is implemented using fork(), wait(), and one of the exec family functions (no use of system()).
10. The shell supports the "cd" command to change directories, including handling "cd ..".
11. The shell supports the "listpids" command to list the PIDs of the last 20 processes spawned by the shell.
12. The shell supports the "history" command, which lists the last 15 commands entered by the user. It can also rerun a command by typing "!n" (n is a number between 0 and 14).
