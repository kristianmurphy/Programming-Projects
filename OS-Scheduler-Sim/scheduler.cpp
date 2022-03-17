#include <iostream>
#include <iomanip> 
#include <string>
using namespace std;

/*
*To test individual scheduler simulations, see scheduler functions called from main() at the bottom
3 CPU Scheduling algorithms
Utilizes custom class PCB to manage process
Keeps data private and uses accessor/mutator functions
*/


class PCB; // Class prototype for PCB (Process Control Block)
void simulation(string scheduler); // Prototype for simulation function - passes input string scheduler, which could be "SJF", "FCFS", or "MLFQ"


class PCB // Class PCB to keep track of information for each process - Data members:
{
public: // Public data of PCB class includes the accessor and mutator functions of the class
    PCB* getLast();  // Used to quickly access the end of the list in each state going through the pcbPointers of each PCB
    PCB* getShortest(); // Used to find the shortest process in the list
    PCB* getFirstPriority(int ipriority);  // Used to find the first process in list with the input priority, called on head of ready list in mlfq
    PCB* getpcbPointer() { return pcbPointer; }  // Accessor for the pcb pointer var
    PCB() { newProcess(); }  // Default value constructor using new process function - is not new state yet (until process ID and data are assigned)
    PCB(int num, int* array, int arraysize);  // Explicit value constructor assigns process ID and pointer to process data array, setting the process in new state
    int remainingBurst() { return dataTime - (ioTime + cpuTime); } // Return the difference between the total burst time accumulation and the taken burst time
    int getLength(); // Get the length of list starting from this PCB and going through the pcbPointers
    int getPriority() { return priority; }  // accessor for priority var

    void newProcess();  // Called by constructor to initialize PCB default values
    void admitProcess(PCB** ready);  // After Explicit value constructor is called, the process is admitted to the ready queue
    void runProcess(PCB** ready, PCB** running, int time);  // Runs process from ready state
    void waitProcess(PCB** running, PCB** waiting);  // Sends the process to waiting list from running state
    void readyProcess(PCB** waiting, PCB** ready);  // Sends the process to ready queue from waiting state (or running, if substituted waiting pointer with running for mlfq preemption)
    void terminateProcess(PCB** running, PCB** terminated, int time);  // Terminates process from running state

    void cpuManage(PCB** running, PCB** waiting, PCB** terminated, int time);  // Determines whether process in cpu should go to waiting or terminated states if at the end of cpu burst
    void waitManage(PCB** waiting, PCB** ready);  // Determines whether process in waiting list should go to ready queue

    void waitTiming() { waitingTime++; if (pcbPointer != NULL) { pcbPointer->waitTiming(); } }
    void cpuTiming() { cpuTime++; if (pcbPointer != NULL) { pcbPointer->cpuTiming(); } }
    void ioTiming() { ioTime++; if (pcbPointer != NULL) { pcbPointer->ioTiming(); } }

    void printStatus(); // Prints the status of process to indicate its progress in CPU, IO, Ready queue, or termination
    void printTable(PCB* head, int id); // Prints the final values in each process, in order P1 to Px (Called recursively uusing head pointer to scan for numeric order in terminated list)

    void incrementPC();  // Increments the time variables for io, cpu, and waiting times
    void decrementTQ() { timeQuantum--; }  // Decrements the time quantum var by 1

    void cpuManageMLFQ(PCB** ready, PCB** running, PCB** waiting, PCB** terminated, int time); // Separate CPU manage function called by MLFQ scheduler for preemption with higher priority process
    

private: // Private data of PCB class includes the variables holding information to each process
    string processState; // Keep track of which state this process should be in
    int processID;      // Keep track of process number (P1-8)
    PCB* pcbPointer;   // Pointer to next PCB - Used in each state to keep track of the order of PCBs
    int* processData; // Pointer to the first CPU burst of the process data (CPU and IO burst) array
    int dataSize;    // A variable saved with the process data to remember the size of its array
    int dataIndex;  // Keep track of which burst the process is on starting with 0
    int dataTime;  // The total ammount of accumulated burst time including cpu and io
    int waitingTime;         // Accumulate 1 for every time unit spent in waiting queue
    int cpuTime;            // Accumulate 1 for every time unit spent in CPU
    int ioTime;            // Accumulate 1 for every time unit spent in I/O
    int responseTime;     // Record the first time of execution in each process
    int terminationTime; // Record the time that the process is terminated
    int priority;       // Current priority of the process, to be initialized in a new process at 1, and goes up to 3
    int timeQuantum;   // Current tq of the process, to be initialized in a new process at 5
};



void PCB::newProcess() {     // Called in constructor to initialize variables to default values
    pcbPointer = NULL;      // Initialize pointer as null
    waitingTime = 0;       // Accumulate 1 for every time unit spent in waiting queue
    cpuTime = 0;          // Accumulate 1 for every time unit spent in CPU
    ioTime = 0;          // Accumulate 1 for every time unit spent in I/O
    dataIndex = -1;     // Start program counter at -1 since execution hasn't yet started (sets to 0 when start, then increments)
    dataTime = 0;      // Start the total time at 0 before accumulating
    priority = 1;     // Start priority at 1 (highest) before potential lowering
    timeQuantum = 5; // Start time quantum at 5 for priority 1 - decrements over time in cpu
    responseTime = -1;  // Start response time at -1 to indicate that it has not been set yet - upon first execution of the process this will be set to the time of execution start
    processState = ""; // Start process state at "" (empty string) to indicate that it has not been fully created yet - upon being given a processID and data, it can be a new process
}

PCB::PCB(int num, int* array, int arraysize) {
    newProcess();             // Initialize process with program counter = 0
    processState = "new";    // Initialize a process in new state
    processID = num;        // Initialize process with given process ID (P1-8)
    processData = array;   // Assign the input array to the data pointer
    dataSize = arraysize; // Keep the passed function argument of array size as var
}

PCB* PCB::getLast() { // Calls recursively on itself to return the very last PCB pointer in a list, calling first on the head of list
    if (pcbPointer == NULL) { return this; } // If at the last PCB of the list, the next pointer will be null (and if the list is only 1 PCB)
    else { return pcbPointer->getLast(); }  // Otherwise call recursively on the next PCB pointer, eventually returning the last one all the way back
}

PCB* PCB::getShortest() {  // Used for SJF scheduling to find the shortest job in the ready queue, by calling recursively starting with the head of the list
    if (pcbPointer == NULL) { return this; }  // If the next PCB pointer is NULL, which means the end of the list, (or list is only 1 PCB) return the current PCB
    else {  // Otherwise compare the next PCB pointer's next CPU burst to the current PCB's next CPU burst which is found through the processData array and using the index+1 for next burst
        if (pcbPointer->getShortest()->processData[pcbPointer->getShortest()->dataIndex + 1] < processData[dataIndex + 1]) { return pcbPointer->getShortest(); }
        else { return this; }  // If the current PCB's CPU burst is greater than or equal to the next (lower) PCB's CPU burst, return this pointer
    }
}

void PCB::admitProcess(PCB** ready) { // Used to admit processes in the new state into the ready state at the beginning of the simulation (since all processes arrive at t=0)
    if ((processState == "new") && ready != NULL) { // First check if the PCB's process state is at new and that the pointer to ready list pointer is not null
        processState = "ready";  // If so, set the current process state to ready (If not, then the *ready list pointer must not have been found from the **ready double pointer)
        if (*ready == NULL) { *ready = this; }  // If the ready list pointer is null (empty list), set the head of the list to this process
        else { (*ready)->getLast()->pcbPointer = this; } // If the ready list is not empty, then get the very last PCB in that list and then add the current PCB onto the end of its next pointer
    }  // If the double pointer was not found or the process was not in the new state (must be in new to be 'admitted' to ready)
    else { cout << "Could not admit process " << processID << " - [" << processState << "]" << endl; } // Print error message
}

void PCB::runProcess(PCB** ready, PCB** running, int time) {  // moves process from ready list to running, preempting 
    if (processState == "ready") {  // First check if process is in ready state (process can only go into running state from ready)
        processState = "running";  // Set current process state to running
        if (*ready == this) {     // If the head of the ready list is the current PCB
            *ready = pcbPointer; // set the head of ready list to this PCB's next pointer (if null, then list is empty)
        }
        else { // Otherwise (if the current PCB is not the head of the ready list)
            PCB* temp = *ready;  // Use temporary pointer to go through ready list to find the preceding PCB to the current one
            if (temp->pcbPointer != NULL) {  // If the temporary PCB's pointer to next PCB (in ready list) is valid:
                while (temp->pcbPointer != this) { temp = temp->pcbPointer; } // Go through each of the descendants of the temporary PCB pointer
                temp->pcbPointer = temp->pcbPointer->pcbPointer; // After using while loop to find parent of running PCB, set its next PCB pointer to the current PCB's next pointer to mend the list
            }
        }
        *running = this;    // Set the running pointer to the current PCB
        pcbPointer = NULL; // Set the next PCB pointer to NULL since there is only 1 process running at a time (no 'next' pointers in running)
        if (responseTime == -1) { responseTime = time; } // set response time when process is ran (if first time -1)

    } // Otherwise:  (if the process state was not "ready" to begin with)
    else { cout << "Could not run process " << processID << " - [" << processState << "]" << endl; } // Print error message
}

void PCB::waitProcess(PCB** running, PCB** waiting) { // Moves current process from running to waiting list
    if (processState == "running") {  // Check if the current PCB's process state is running (can not go to waiting list unless currently running)
        processState = "waiting";    //  If so, update current PCB's process state to waiting
        if (*waiting == NULL) { *waiting = this; }  // If the waiting list head pointer is NULL (list is empty), set the pointer to head of list to the current process
        else { (*waiting)->getLast()->pcbPointer = this; } // If the waiting list is not empty, get the last PCB of the list and set its next pointer to the current process
        *running = NULL;    // Now that the process has been moved to the waiting list, set the running list to NULL (empty)
        pcbPointer = NULL; // Make sure that the pointer to next PCB is set to NULL since the current process is at the very end of the waiting list
    } // Otherwise:  (if the process state was not "running" to begin with)
    else { cout << "Could not move process " << processID << " to waiting queue - " << "[" << processState << "]" << endl; } // Print error message
}

void PCB::readyProcess(PCB** waiting, PCB** ready) {                // Moves process from waiting list to ready queue
    if (processState == "waiting" || processState == "running") {  // Check if the current PCB's proccess state is waiting or ready (can not go to ready queue unless the currently in waiting list, or preempted from running)
        processState = "ready";  // If so, update the current PCB's process state to ready
        if (*waiting == this) { *waiting = pcbPointer; }    // If the head of the waiting(/running) list is the current process: set the new head of the waiting list to the pointer to next PCB (if NULL, empty list)
        else {  // If the current process is not the head of the waiting list:
            PCB* temp = *waiting;             // Set a temporary pointer to PCB as the head of the waiting list
            if (temp->pcbPointer != NULL) {  // Check if pointer is valid
                while (temp->pcbPointer != this) { temp = temp->pcbPointer; }  // Loop through list to find which PCB holds its next pcb pointer to the current process
                temp->pcbPointer = temp->pcbPointer->pcbPointer;  // Increment the temporary pointer to the next pcb
            }
        } // Set the ready list:
        if (*ready == NULL) { *ready = this; } // If the list is empty, initialize it with this PCB
        else { (*ready)->getLast()->pcbPointer = this; }  // Otherise (if it is not empty) add this PCB to the last list item's next pcbPointer
        pcbPointer = NULL;  // Since it is at the end of the list, make sure the next pcb pointer is null
    } // If not in the correct state(s) to begin with:
    else { cout << "Could not move process " << processID << " to ready list - " << "[" << processState << "]" << endl; }  // Print error message
}

void PCB::terminateProcess(PCB** running, PCB** terminated, int time) {
    if (processState == "running") {  // Check if running  (can not terminate from other states)
        if (*terminated == NULL) { *terminated = this; }        // If the terminated list is empty, initialize it with pointer to this PCB
        else { (*terminated)->getLast()->pcbPointer = this; }  // Otherwise (if list is not empty) get the last PCB item of the terminated list and add the current PCB to it's next pointer
        *running = NULL;  // Since the running task has been terminated, set the running pointer to null (empty)
        processState = "terminated";  // Update the process state to terminated
        terminationTime = time;      // Use the time input to the function in order to record the time of termination in var
        pcbPointer = NULL; // Since now at the end of terminated list, make sure next pointer is null
    }                     // Otherwise:  (if state was not running to begin with)
    else { cout << "Could not terminate process " << processID << " - [" << processState << "]" << endl; } // Print error message
}

void PCB::incrementPC() {              // Increments the dataIndex, or program counter index in the array of process data (IO/CPU bursts)
    if (dataIndex + 1 <= dataSize) {  // If the data index is less than the total size of the data array
        dataIndex++;                 // Increment the data index to the next index in the data array
        dataTime += processData[dataIndex];  // Add to the process dataTime with the new processData index so that the total burst time can be saved
    }
}

void PCB::cpuManage(PCB** running, PCB** waiting, PCB** terminated, int time) { // Used by SJF and FCFS schedulers to manage the CPU (called on running pointer if not null)
    if (dataTime - ioTime - cpuTime == 0) { // If the ioTime and cpuTime that the process has taken is subtracted from the total burst time at this stage, and gets, 0, then the current burst must be finished
        if (dataIndex + 1 >= dataSize) { terminateProcess(running, terminated, time); }  // If at the last stage of the CPU/IO bursts, then terminate process
        else { incrementPC();  waitProcess(running, waiting); } // Otherwise (if not at the last burst) increment the index and total burst time from the burst array and send the process to waiting list
    }
}

void PCB::waitManage(PCB** waiting, PCB** ready) { // Used by all schedulers to check if finished with IO burst and can be moved to ready queue (called recursively from the waiting list pointer)
    if (dataTime - ioTime - cpuTime == 0) {       // If finished with the current burst ( total burst time - io/cpu time taken so far: if 0, the burst is at its end )
        PCB* p = pcbPointer;  // Use temporary pointer to the next PCB in the waiting list
        readyProcess(waiting, ready);  // Ready the current process
        if (p != NULL) { p->waitManage(waiting, ready); } // Call recursively on the next PCBs in the waiting list
    }
    else { // Otherwise: (if current burst has not finished)
        if (pcbPointer != NULL) { pcbPointer->waitManage(waiting, ready); }  // If the next pointer is not null, call recursively on it to check the bursts of the other processes
    }
}

void PCB::printStatus() {           // Called at each context switch to recursively go through each process in a list (called on head of list)
    if (processState == "ready") { // If the current process is in ready state
        cout << "P" << processID << " [Next CPU burst: " << processData[dataIndex+1] << "]" << endl; // Print the process ID (P1, P2,.. P8) and burst time
    }
    else if (processState == "running") {     // If the current process is in running state
        cout << "Running: P" << processID << endl; // Print the process ID (P1, P2,.. P8)
    }
    else if (processState == "waiting") {     // If the current process is in waiting state
        cout << "P" << processID << " [Remaining IO burst: " << dataTime - (ioTime + cpuTime) << "]" << endl;  // Print the process ID (P1, P2,.. P8) and its remaining burst time
    }
    else if (processState == "terminated") {  // If the current process is in terminated state
        cout << "P" << processID << " Terminated at time: " << terminationTime << endl;  // Print the process ID (P1, P2,.. P8) and its time of termination from var
    }
    if (pcbPointer != NULL) {  // If the next PCB pointer is valid: 
        if (processState != pcbPointer->processState) { cout << "Error - (" << processID << ") " << processState << " != (" << pcbPointer->processID << ") " << processState << "!" << endl; }
        else {// Check if the next pointer's state different from the current state - if so, print error message
            pcbPointer->printStatus(); // If correct, call recursively on next PCB pointer
        }
    }
}

void PCB::printTable(PCB* head, int id) { // Called at the end of each simulation, prints all details of processes in list (terminated), in numeric order
    if (id < head->getLength()) {  // Check if the process number is still less than list length:
        PCB* search = head;  // Use temporary PCB pointer search starting at the head of the list to go through and find the next process
        while (search != NULL && search->processID != id + 1) { search = search->pcbPointer; } // Use loop to go through list and find the next numeric process ID
        if (search != NULL) { // If not found, the search pointer will be null - however if found:
            if (id + 1 == 1) { search->ioTime--; } else { search->waitingTime--; }  // Adjust timing for accurate result
            cout << "P" << search->processID << "    Tw = " << (search->waitingTime) << "    Ttr = " << (search->waitingTime  + search->ioTime + search->cpuTime) << "    Tr = " << search->responseTime << endl;
        }  // Print the results in order of instruction sample format ^
        search->printTable(head, id + 1);  // Call recursively on next item in list
    }
    else if (id == head->getLength()) { // Check if finished printing list of process details
        float avgTw = 0;      // Initialize average waiting time variable for calculation
        float avgTtr = 0;    // Initialize average turnaround time variable for calculation
        float avgTr = 0;    // Initialize average response time variable for calculation
        PCB* i = head;     // Use temporary pointer i initialized at the head of the list to loop through
        int avgcount = 0; // Initialize variable to hold the count of # of averaged values
        while (i != NULL) {  // Use loop to go through list and accumulate average var if i is valid
            avgTw += i->waitingTime;  // Accumulate avg waiting time
            avgTtr += i->waitingTime + i->ioTime + i->cpuTime; // Accumulate avg turnaround time (waiting time + io time + cpu time)
            avgTr += i->responseTime; // Accumulate avg response time
            i = i->pcbPointer;  // Set i to the next PCB pointer to average next PCB values
            avgcount++;  // Increment the number of averaged values for each var
        }
        avgTw = avgTw / avgcount;  // average = accumulated values / total num of values
        avgTtr = avgTtr / avgcount; // average = accumulated values / total num of values
        avgTr = avgTr / avgcount; // average = accumulated values / total num of values
        cout << "Avg" << "   Tw = " << avgTw << "    Ttr = " << avgTtr << "    Tr = " << avgTr << endl; // Print the averages
    }
}

int PCB::getLength() {  // Used to get length of the current list (called on the head of list)
    PCB* p = this;  // Use temporary pointer p for loop
    int count = 1; // Initialize count variable at 1 since the current PCB counts as 1 length
    while (p != NULL) { p = p->pcbPointer; count++; } // If temporary pointer p is not null, go to the next pointer and increment the count
    return count;  // When pointer p is finally null, return the number of iterations (length)
}

PCB* PCB::getFirstPriority(int ipriority) { // Called on the head of the ready list to find first PCB with the input priority, ipriority
    if (priority == ipriority) { // If the priority matches:
        return this;  // Return pointer to the current PCB
    }
    else {  // Otherwise:  (if it doesn't match)
        if (pcbPointer == NULL) { return NULL; }  // If at the end of the list, return null since the priority was not found in any process
        else { return pcbPointer->getFirstPriority(ipriority); }  // Otherwise (priority not found, and not at end of the list) call recursively on next PCB pointer!
    }
}

// called to manage CPU
void PCB::cpuManageMLFQ(PCB** ready, PCB** running, PCB** waiting, PCB** terminated, int time) {  // Called in MLFQ scheduler to check 
    if (dataTime - ioTime - cpuTime == 0) { // If the burst is finished:  (if the total burst time - total io/cpu time = 0)
        if (priority == 1) {timeQuantum=5; } else if (priority == 2) { timeQuantum=10; }  // Reset the time quantum based on priority
        if (dataIndex + 1 >= dataSize) { terminateProcess(running, terminated, time); }  // If finished the last burst, terminate the process
        else { incrementPC();  waitProcess(running, waiting); }  // If not on the last burst, send to waiting queue
    }
    else if ((priority==1 || priority==2) && timeQuantum == 0) { // If the time quantum is finished before the burst:
        if (priority == 1) { priority++; timeQuantum=10; } else if (priority == 2) { priority++; } // If priority is 1 or 2, increment, if the priority was 1 then the tq goes to priority 2 tq (tq=10)
        readyProcess(running, ready);  // Send process to ready queue
    }
    else if (*ready != NULL) { // If ready list exists (preemption)
        if ((priority == 2 || priority == 3) && (*ready)->getFirstPriority(1) != NULL) { // If the priority of current process is 2 or 3 and there is a priority 1 process in ready queue ready to preempt:
            if (priority == 2) { timeQuantum = 10; } // If the priority of this process (preempted) is 2, then reset its tq at 10 for next run
            readyProcess(running, ready);  // Send the current process to the ready queue since it is preempted - on next section of scheduler the highest priority process will run
            cout << "\nPREEMPTION: time:" << time << " Currently running: P" << processID << " p" << priority << "  Preemption from: P" << (*ready)->getFirstPriority(1)->processID << " p" << (*ready)->getFirstPriority(1)->priority << endl;
        } // Print message
        else if (priority == 3 && (*ready)->getFirstPriority(2) != NULL) { // If the priority of the current process is 3 and there is a priority 2 process in the ready queue ready to preempt:
            readyProcess(running, ready); // Send the current process to the ready queue since it is preempted - on next section of scheduler the highest priority process will run
            cout << "\nPREEMPTION: time:" << time << " Currently running: P" << processID << " p" << priority << "  Preemption from: P" << (*ready)->getFirstPriority(2)->processID << " p" << (*ready)->getFirstPriority(2)->priority << endl;
        } // Print message
    }
}



// Non-member functions: //

void programCounter(PCB* ready, PCB* running, PCB* waiting) { // Called in schedulers to call on class functions to increment timings
    if (ready != NULL) { ready->waitTiming(); }      // If ready queue has PCBs, call recursive function wait Timing to increment all of the waiting times
    if (running != NULL) { running->cpuTiming(); }  // If cpu has a PCB, call recursive function wait Timing to increment cpu Time
    if (waiting != NULL) { waiting->ioTiming(); }  // If waiting list has PCBs, call recursive function wait Timing to increment all of the io times
}

void scheduleSJF(PCB** ready, PCB** running, PCB** waiting, PCB** terminated) {  // SCHEDULER - Shortest Job First scheduling simulation
    if (ready != NULL && running != NULL && waiting != NULL && terminated != NULL) { // If the double pointers to the pre-initialized lists are valid, proceed:
        int idleTime = 0;  // initialize integer idleTime to keep track of how long the cpu is idle (no running processes, or *running = null)
        for (int t = 0; t <= 1024; t++) {  // TIME loop - time units t
            if (*waiting != NULL) {  // If there is at least one process in the waiting list:   (or not null)
                (*waiting)->waitManage(waiting, ready); // call wait manage to manage the waiting list
            }  // next:
            if (*running != NULL) {  // If there is a process running:
                (*running)->cpuManage(running, waiting, terminated, t); // Call cpuManage to determine what to do with the running process
            }  // next:
            if (*running == NULL) {     // Check if no processes are running (no preemption)
                if (*ready != NULL) {  // If there is a process in ready queue:
                    (*ready)->getShortest()->runProcess(ready, running, t);  // Run shortest process in ready queue
                    (*running)->incrementPC(); // Increment the progam counter upon run
                    cout << "\n[SJF] Current Execution time: " << t << endl; // Print scheduler type, and the current exec time
                    (*running)->printStatus(); // Print the status of the process currently running
                    if (*ready != NULL) { cout << "Ready:" << endl; (*ready)->printStatus(); } // If something in ready list, call recursive print status on list head to print the whole list
                    if (*waiting != NULL) { cout << "Waiting:" << endl; (*waiting)->printStatus(); } // If something in waiting list, call recursive print status on list head to print the whole list
                    if (*terminated != NULL) { cout << "Terminated:" << endl; (*terminated)->printStatus(); } // If something in terminated list, call recursive print status on list head to print the whole list
                }
            }
            if (*ready == NULL && *waiting == NULL && *running == NULL) { // If all queues are finished then print final table and end loop
                if (*terminated != NULL) { // If the terminated list is valid and not empty:   (All processes should end up in terminated list)
                    cout << "\nSJF Results:\nTotal time: " << t-1 << "  CPU Utilization: " << (1 - (float)idleTime / (t-1)) * 100 << "%" << endl; // Print the scheduler type, total time taken, and CPU utilization
                    (*terminated)->printTable(*terminated, 0); // Then print all of the processes in table (in terminated list)
                } // finished
                return;
            }
            else { // Otherwise:   (if the lists are not empty)
                if (*running == NULL) { idleTime++; } // If there is nothing running, increment the idleTime var
                programCounter(*ready, *running, *waiting); // Increment the waiting, cpu, and io times
            }
        }
    }
}

void scheduleFCFS(PCB** ready, PCB** running, PCB** waiting, PCB** terminated) { // SCHEDULER - First Come First Serve scheduling simulation
    if (ready != NULL && running != NULL && waiting != NULL && terminated != NULL) {  // If the double pointers to the pre-initialized lists are valid, proceed:
        int idleTime = 0;  // initialize integer idleTime to keep track of how long the cpu is idle (no running processes, or *running = null)
        for (int t = 0; t <= 1024; t++) {  // TIME loop - time units t
            if (*waiting != NULL) { // If there is at least one process in the waiting list:   (or not null)
                (*waiting)->waitManage(waiting, ready); // call wait manage to manage the waiting list
            } // next:
            if (*running != NULL) {  // If there is a process running:
                (*running)->cpuManage(running, waiting, terminated, t);  // Call cpuManage to determine what to do with the running process
            } // next:
            if (*running == NULL) {     // Check if no processes are running (no preemption)
                if (*ready != NULL) {  // If there is a process in ready queue:
                    (*ready)->incrementPC(); // Increment the progam counter upon run
                    (*ready)->runProcess(ready, running, t);  // Run first process in ready queue
                    cout << "\n[FCFS] Current Execution time: " << t << endl; // Print scheduler type, and the current exec time
                    (*running)->printStatus(); // Print the status of the process currently running
                    if (*ready != NULL) { cout << "Ready:" << endl; (*ready)->printStatus(); } // If something in ready list, call recursive print status on list head to print the whole list
                    if (*waiting != NULL) { cout << "Waiting:" << endl; (*waiting)->printStatus(); } // If something in waiting list, call recursive print status on list head to print the whole list
                    if (*terminated != NULL) { cout << "Terminated:" << endl; (*terminated)->printStatus(); } // If something in terminated list, call recursive print status on list head to print the whole list
                }
            }
            if (*ready == NULL && *waiting == NULL && *running == NULL) { // If all queues are finished then print final table and end loop
                if (*terminated != NULL) { // If the terminated list is valid and not empty:   (All processes should end up in terminated list)
                    cout << "\nFCFS Results:\nTotal time: " << t - 1 << "  CPU Utilization: " << (1 - (float)idleTime / (t - 1)) * 100 << "%" << endl; // Print the scheduler type, total time taken, and CPU utilization
                    (*terminated)->printTable(*terminated, 0); // Then print all of the processes in table (in terminated list)
                } // Finished 
                return;
            }
            else { // Otherwise:   (if the lists are not empty)
                if (*running == NULL) { idleTime++; } // If there is nothing running, increment the idleTime var
                programCounter(*ready, *running, *waiting); // Increment the waiting, cpu, and io times
            }
        }
    }
}

void scheduleMLFQ(PCB** ready, PCB** running, PCB** waiting, PCB** terminated) { // SCHEDULER - MultiLevel Feedback Queue scheduling simulation
    if (ready != NULL && running != NULL && waiting != NULL && terminated != NULL) { // If the double pointers to the pre-initialized lists are valid, proceed:
        int idleTime = 0; // initialize integer idleTime to keep track of how long the cpu is idle (no running processes, or *running = null)
        for (int t = 0; t <= 1024; t++) {  // TIME loop - time units t
            //bool runstart = false; 
            if (*waiting != NULL) {  // If there is at least one process in the waiting list:   (or not null)
                (*waiting)->waitManage(waiting, ready);  // call wait manage to manage the waiting list
            } // next:
            if (*running != NULL) { // If there is a process running:
                (*running)->cpuManageMLFQ(ready, running, waiting, terminated, t);   // Call cpuManageMLFQ to determine what to do with the running process
            } // next:
            if (*ready != NULL) {  // If there is a process in ready queue:
                if (*running == NULL) { // If not running anything
                    if ((*ready)->getFirstPriority(1) != NULL) { // Get the first priority 1 process
                        if ((*ready)->getFirstPriority(1)->remainingBurst() <= 0) { ((*ready)->getFirstPriority(1))->incrementPC(); } // If the burst is up, increment program counter
                        ((*ready)->getFirstPriority(1))->runProcess(ready, running, t); // Run the process
                    } // If there is no priority 1 process: 
                    else if ((*ready)->getFirstPriority(2) != NULL) { // Get the first priority 2 process
                        if (((*ready)->getFirstPriority(2))->remainingBurst() <= 0) { ((*ready)->getFirstPriority(2))->incrementPC(); } // If the burst is up, increment program counter
                        ((*ready)->getFirstPriority(2))->runProcess(ready, running, t); // Run the process
                    } // If there is no priority 2 process:
                    else { //Priority 3:  (and above 3, although processes should never go above priority value 3)
                        if ((*ready)->remainingBurst() <= 0) { (*ready)->incrementPC(); } // If the burst is up, increment program counter
                        (*ready)->runProcess(ready, running, t); // Run the process
                    }
                }
                cout << "\n[MLFQ] Current Execution time: " << t << endl;   // Print scheduler type, and the current exec time
                (*running)->printStatus();  // Print the status of the process currently running
                if (*ready != NULL) { cout << "Ready:" << endl; (*ready)->printStatus(); } // If something in ready list, call recursive print status on list head to print the whole list
                if (*waiting != NULL) { cout << "Waiting:" << endl; (*waiting)->printStatus(); } // If something in waiting list, call recursive print status on list head to print the whole list
                if (*terminated != NULL) { cout << "Terminated:" << endl; (*terminated)->printStatus(); } // If something in terminated list, call recursive print status on list head to print the whole list
            }
            if (*ready == NULL && *waiting == NULL && *running == NULL) {  // If all queues are finished then print final table and end loop
                if (*terminated != NULL) {  // If things in terminated list:
                    cout << "\nMLFQ Results\nTotal time: " << (t-1) << "  CPU Utilization: " << (1 - (float)idleTime / (t-1)) * 100 << "%" << endl; // Print the scheduler type, total time taken, and CPU utilization
                    (*terminated)->printTable(*terminated, 0);// Then print all of the processes in table (in terminated list)
                } // Finished
                return;
            }
            else { // Otherwise:   (if the lists are not empty) 
                if (*running == NULL) { idleTime++; }  // If there is nothing running, increment the idleTime var
                else { (*running)->decrementTQ(); } // Otherwise (if something is running) call decrement tq to decrement the time quantum every time unit that it runs
                programCounter(*ready, *running, *waiting); // Increment the waiting, cpu, and io times  // Increment the waiting, cpu, and io times
            }
        }
    }
}

void runSimulation(string scheduler) { // Function to call a scheduler simulation, using fresh list pointers and data each time called
    // Create the states of OS
    PCB* readyList = nullptr; // first PCB of the ready list
    PCB* runningList = nullptr; // PCB that is currently running in the CPU
    PCB* waitingList = nullptr; // PCB waiting list
    PCB* terminatedList = nullptr; // terminated processes

    // Create the process data inputs for process CPU bursts and I/O times
    int P1[] = { 5, 27, 3, 31, 5, 43, 4, 18, 6, 22, 4, 26, 3, 24, 5 };
    int P2[] = { 4, 48, 5, 44, 7, 42, 12, 37, 9, 76, 4, 41, 9, 31, 7, 43, 8 };
    int P3[] = { 8, 33, 12, 41, 18, 65, 14, 21, 4, 61, 15, 18, 14, 26, 5, 31, 6 };
    int P4[] = { 3, 35, 4, 41, 5, 45, 3, 51, 4, 61, 5, 54, 6, 82, 5, 77, 3 };
    int P5[] = { 16, 24, 17, 21, 5, 36, 16, 26, 7, 31, 13, 28, 11, 21, 6, 13, 3, 11, 4 };
    int P6[] = { 11, 22, 4, 8, 5, 10, 6, 12, 7, 14, 9, 18, 12, 24, 15, 30, 8 };
    int P7[] = { 14, 46, 17, 41, 11, 42, 15, 21, 4, 32, 7, 19, 16, 33, 10 };
    int P8[] = { 4, 14, 5, 33, 6, 51, 14, 73, 16, 87, 6 };

    // Create array of PCBs from process data
    PCB pcbArray[] = { // Use explicit value constructor to pass the process ID number, the array of CPU/IO bursts, and the data array size, respectively
        PCB(1,P1,sizeof(P1) / sizeof(P1[0])),
        PCB(2,P2,sizeof(P2) / sizeof(P2[0])),
        PCB(3,P3,sizeof(P3) / sizeof(P3[0])),
        PCB(4,P4,sizeof(P4) / sizeof(P4[0])),
        PCB(5,P5,sizeof(P5) / sizeof(P5[0])),
        PCB(6,P6,sizeof(P6) / sizeof(P6[0])),
        PCB(7,P7,sizeof(P7) / sizeof(P7[0])),
        PCB(8,P8,sizeof(P8) / sizeof(P8[0]))
    };
    // Use for-loop to go through the array of PCBs and admit each into the ready list
    for (int i = 0; i < sizeof(pcbArray) / sizeof(pcbArray[0]); i++) { (pcbArray[i]).admitProcess(&readyList); }
    // Run the scheduler passed in the scheduler string input, with the list pointer addresses passed in:
    if (scheduler == "SJF") {
        scheduleSJF(&readyList, &runningList, &waitingList, &terminatedList);
    }
    else if (scheduler == "FCFS") {
        scheduleFCFS(&readyList, &runningList, &waitingList, &terminatedList);
    }
    else if (scheduler == "MLFQ") {
        scheduleMLFQ(&readyList, &runningList, &waitingList, &terminatedList);
    }
    else { cout << "\nInvalid scheduling type! (check main)\nValid types are:\nSJF\nFCFS\nMLFQ\n"; }
 
    return;
}


int main()
{
    // Do three simulations, one for each scheduler:
    runSimulation(string("SJF"));
    runSimulation(string("FCFS"));
    runSimulation(string("MLFQ"));
    return 0;
}
