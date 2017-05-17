# PThreadSignals
Project for Introduction to Computer Systems involving signals and pthreads

Summary of Problem:

Use IPC utilizing signals to pass information to forked children processes. These processes will find the max, min, and sum of a randomly generated list of numbers. See the description below for more details.

FORMAL PROBLEM DESCRIPTION:

Part A) The IPC is now to be conducted with signals and signal handlers but not with Pipes or Shared
Memory. You should go over the available signals and figure out how to pass information from
the parent to the child and vice versa through signals/interrupts/signal handlers.

Part B) Your parent process becomes now very impatient…. It does not want to wait for any child
process longer than 3 seconds. If a child process takes longer than this, do not incorporate the
contribution of this process to the final result. And not only this alone, but the parent should
“mark” the slow behaving processes and “notify” all its children processes about “who” this
misbehaving process is. And then, have any or all of the rest of children processes attempt to
terminate this one (before the parent comes in). What do you observe if more than one process
attempts to terminate a given process? Write the proper instructions that ensure all the questions
in this part, and figure out the proper signals to be incorporated again either by the parent or the
children processes.

Part C) The user running this program (… this is your group) got very impatient while waiting for all
these calculations to be conducted, and decides to be done with the whole experiment by typing:
i) CTL-C, ii) select your own interrupt, iii) also the user may want to experiment and attempt to
terminate certain processes (children or parent). Your program should contain signal handlers that
take care of these actions and give back to the user information about what type of interrupt was
issued, on which process, and you may print any other related output that helps the user get more
info about the process. Also, you may want to change the handlers to “block” the processes from
termination or suspension or in general of accepting the signals. We have defined 3 cases above
(i, ii, iii). When can you do the latter and when not? For the cases that you can, please show how
you have incorporated this capability to your code and your results.

COMPILING INSTRUCTIONS:


PART A - PartA.c
PART B - PartB.c
PART C - PartC.c

Execute the following line while running terminal in the proper directory

gcc -Wall -o PartA PartA.c -pthread
./PartA

where 'PartA' and 'PartA.c' can be changed to the other parts of this problem

The input and output files are automatically generated.

IMPORTANT: Please delete the input and output file in between running each program. 
Failure to do so will result in an incorrect execution of the program and possible errors.

IMPORTANT FOR PART B: In order to simulate children not responding, infinite while loops (while(1){}) were put in the signal overwrites for each function.
The signals are: SIGBUS, SIGILL, SIGHUP, SIGSYS, SIGPWR, SIGTTOU.
These infinite while loops were commented out for submission, but just uncommenting these while loops will still simulate a child taking too long.

