# Operating System Scheduler simulation
Different combinations of CPU scheduler algorithms can yield different results, some
better than others overall, but each CPU scheduler has its own advantages and disadvantages.
In this comparison of CPU schedulers, three schedulers are taken into consideration: Shortest
Job First (SJF), First Come First Serve (FCFS), and MultiLevel Feedback Queue (MLFQ).
Through implementation of these schedulers in a simulation of which I programmed with C++,
the advantages and disadvantages of each scheduling algorithm become apparent.
Throughout my simulation program, the following are recorded for each process:
response time, between the time of the process’ arrival and its first execution; waiting time,
which accumulates as the process is in the ready list; and turnaround time, which is the waiting
time added with the recorded times spent in I/O and CPU. Many more variables listed in my
C++ code keep track of certain values for certain calculations and results including priority,
process state, time quantum, and termination time in the class called “PCB” (Process Control
Block). All of the process-specific data is kept private to the PCB class, and can only be read or
written to by the accessor and mutator member functions, which are public in the class.

The design of my three scheduling algorithm programs is largely based on my
interpretation of the operating state diagram and how it is traversed by different algorithms. In
my progression in constructing the programs, however, it began to take a slightly less logical
turn as I touched up certain lines of code that would be more efficient if run a different way. It
started with just a PCB class to store the information to each unique process like a fully
functional operating system would have, giving the process an ID number (P1 - 8) and a pointer
variable to store in memory the address of the next process in order (PCB Pointer). Then I
created the simulation function, which initializes the running pointer and the ready queue,
waiting list, terminated list head pointers and then puts all of the active processes in the ready
queue - from there, this simple program began to evolve quite rapidly.

To simulate the progression of time, I used a for-loop that repeats a scheduling algorithm
over and over, incrementing its loop index by 1 each time. Next, in an effort to condense the
length of each scheduling algorithm, I created the basic functionalities of scheduling processes
in member functions to the PCB class, such as runProcess(), readyProcess(), waitProcess(),
and terminateProcess(). However, this implementation of scheduling would later become more
complex as I started building these functionalities around the First Come First Serve algorithm,
which is the simplest here - these 4 functions would soon grow to over 20 total member
functions (this does not include the non-member functions defined outside of the class).
The way this program actually executes is by having three separate scheduling algorithm
functions, and one calling function runSimulation(string scheduler). This function takes an input
of either “SJF”, “FCFS”, or “MLFQ” and then creates the process states and the processes.
Each IO/CPU burst must be specified in the function in arrays for each process - this will then be
passed into the process constructor function, which initializes the process c++ objects of class
type PCB, and admits each of these processes in the “new'' state to the ready queue. Then
based on the input of the scheduler type, this function invokes the scheduling algorithm to run
until it completes. This entire functionality is repeated three times, one for each scheduler type
in the main() function:
runSimulation(string("SJF"));
runSimulation(string("FCFS"));
runSimulation(string("MLFQ"));
The dynamic execution calculations and final results of each simulation are printed to the screen
one after another. To view one at a time, simply remove all but one function call (or convert to
comment, or change scheduler type)
