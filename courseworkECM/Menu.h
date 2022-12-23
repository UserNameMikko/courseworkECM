#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>


const int N = 5;
double Pn;
int M, K, Kr;

struct Processor {
	int memoryBlock; // the memory block that this processor accesses the most
	int commandsExecuted; // number of commands that have been executed by this processor
	int waitingTime; // time spent waiting for the bus or switch channel
};

// Shared bus communication system
int busSystem(std::vector<Processor>& processors, bool out) {
    int maxTotalTime = -1;
    for (int i = 0; i < N; ++i) {
        processors[i].waitingTime = 0;
    }
    int busOwner = -1; // the processor that currently owns the bus
    while (true) {
        bool allDone = true; // flag to check if all processors have finished executing their programs
        for (int i = 0; i < N; ++i) {
            if (processors[i].commandsExecuted < K) {
                allDone = false;
                if (busOwner == i) {
                    // Processor i owns the bus and can execute a command
                    ++processors[i].commandsExecuted;
                    if (processors[i].commandsExecuted <= Kr) {
                        // Command does not require access to external memory
                    }
                    else {
                        // Command requires access to external memory
                        int memory_block = (processors[i].commandsExecuted - Kr - 1) % (N - 1) + (processors[i].memoryBlock == 0 ? 1 : 0);
                        processors[i].waitingTime += M;
                    }
                }
                else {
                    // Processor i does not own the bus and must wait for its turn
                    ++processors[i].waitingTime;
                }
                if(out)
                    std::cout << "Processor" << i + 1 << " Commands executed: " << processors[i].commandsExecuted << " Memory block: " << processors[i].memoryBlock <<
                    " waiting time: " << processors[i].waitingTime << std::endl;
            }
            maxTotalTime = maxTotalTime < processors[i].waitingTime ? processors[i].waitingTime : maxTotalTime;
        }
        if (allDone) {
            // All processors have finished executing their programs
            break;
        }
        // Rotate bus ownership to the next processor
        busOwner = (busOwner + 1) % N;
    }
    return maxTotalTime;
}

// Switch-based communication system
int switchBasedSystem(std::vector<Processor>& processors, bool out) {
    int maxTotalTime = -1;
    for (int i = 0; i < N; ++i) {
        processors[i].waitingTime = 0;
    }
    while (true) {
        bool allDone = true; // flag to check if all processors have finished executing their programs
        for (int i = 0; i < N; ++i) {
            if (processors[i].commandsExecuted < K) {
                allDone = false;
                // Processor i can execute a command
                ++processors[i].commandsExecuted;
                if (processors[i].commandsExecuted <= Kr) {// Command does not require access to external memory

                }
                else {// Command requires access to external memory
                    int memory_block = (processors[i].commandsExecuted - Kr - 1) % (N - 1) + (processors[i].memoryBlock == 0 ? 1 : 0);
                    processors[i].waitingTime += M;
                }
                if(out)
                    std::cout << "Processor" << i + 1 << " Commands executed: " << processors[i].commandsExecuted << " Memory block: " <<
                    processors[i].memoryBlock << " waiting time: " << processors[i].waitingTime << std::endl;
            }
            maxTotalTime = maxTotalTime < processors[i].waitingTime ? processors[i].waitingTime : maxTotalTime;
        }
        if (allDone) {
            // All processors have finished executing their programs
            std::cout << "All done!" << std::endl;
            break;
        }
    }
    return maxTotalTime;
}

void inputValues() {
    std::string firstValues = "Pn = 0.9 Kr = 0.9; M = 2; K = 5";
    std::string secondValues = "Pn = 0.6 Kr = 0.6; M = 10; K = 10";
    std::cout << "start values" << std::endl << "N = 5" << std::endl << "1 - " << firstValues << std::endl
        << "2 - " << secondValues << std::endl;
    int c;
    do {
        std::cin >> c;
        switch (c) {
            case 1:
                Pn = 0.9;
                Kr = static_cast<int>(K * 0.9);
                M = 2;
                K = 5;
                std::cout << "Your choice is " << firstValues << std::endl;
                break;
            case 2:
                Pn = 0.6;
                Kr = static_cast<int>(K * 0.6);
                M = 10;
                K = 10;
                std::cout << "Your choice is " << secondValues << std::endl;
                break;
            default:
                std::cout << "Your input value is incorrect!" << std::endl;
                break;
        }        
    } while (c != 1 && c != 2);
    std::vector<Processor> processors(N);
    
    for (int i = 0; i < N; ++i) {
        processors[i].memoryBlock = i;
        processors[i].commandsExecuted = 0;
    }
    std::cout << "need to out all info about program work? 1/0:" << std::endl;
    int choice;
    std::cin >> choice;
    bool out = choice == 1;
    std::cout << "Shared bus system:" << std::endl;
    int busResult = busSystem(processors, out);
    for (int i = 0; i < N; ++i) {
        std::cout << "Processor " << i + 1 << ": waiting time = " << processors[i].waitingTime << std::endl;
    }

    std::cout << "\nSwitch-based system:" << std::endl;
    for (int i = 0; i < N; ++i) {
        processors[i].commandsExecuted = 0;
    }
    int switchBasedResult = switchBasedSystem(processors, out);
    for (int i = 0; i < N; ++i) {
        std::cout << "Processor " << i + 1 << ": waiting time = " << processors[i].waitingTime << std::endl;
    }
    std::cout << std::endl << std::endl << "max total time for bus:" << busResult << 
        std::endl << "max total time for switch based:" << switchBasedResult << std::endl;

}



void startProgram() {
    inputValues();
}












/*
int Menu::bus() {
    // Initialize random seed
    srand(time(nullptr));
    int maxMemoryAccesses = -1;
    // Loop through each processo
    for (int i = 0; i < N; ++i) {
        int numMemoryAccesses = 0;
        int totalTime = 0;
        // Loop through each command
        for (int j = 0; j < K; ++j) {
            //std::cout << "XXX   " << (double)rand() / RAND_MAX << std::endl;
            // Check if the command requires access to external memory
            bool requiresMemoryAccess = ((double)rand() / RAND_MAX) >= Kr;
            if (requiresMemoryAccess) {
                // Increment the number of memory accesses
                ++numMemoryAccesses;
                // Calculate the time for this command, taking into account memory access time
                totalTime += M;
            }
            else {
                // Command does not require access to external memory, so it takes 1 time unit to execute
                ++totalTime;
            }
        }
        // Finding max time for each processor
        maxMemoryAccesses = maxMemoryAccesses < totalTime ? totalTime : maxMemoryAccesses;
        // Print the results for this processor
        std::cout << "Processor " << i + 1 << ": " << numMemoryAccesses << " memory accesses, total time = " << totalTime << std::endl;
        //std::cout << "max value: " << maxMemoryAccesses << std::endl;
    }
    std::cout << "bus result time:" << maxMemoryAccesses << std::endl;
    return maxMemoryAccesses;
}
int Menu::commutator() {


    return 1;
}*/