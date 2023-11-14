#ifndef MACHINETASK_MACHINE_H
#define MACHINETASK_MACHINE_H

#include <bits/stdc++.h>

using namespace std;

class Memory {
private:
   // string file;
    vector<string>memo;
    vector<string>R;
public:
    Memory(string file);
    void setMemory(string);
    void setR(string);
    friend class Machine;
    friend class Instruction;
};

class Machine {
private:
    string file;
    int programCounter = 0; //?????
public:
//    Machine(vector<string >r, vector<string>m);
//    void loadProgramFile();
    void output();
    void displayMenu();
    string getNextInstruction(string first, string second, string third);
    void runInstruction(string Instruction);
    friend class Instruction;
};

class Instruction {

public:
    Instruction();
    void execute();
    void Load1(string reg, string address);
//    void Load2();
//    void Store();
};
#endif //MACHINETASK_MACHINE_H
