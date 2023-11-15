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
    Memory();
//    void setMemorySize();
//    void setRSize();
    friend class Machine;
    friend class Instruction;
};

class Machine {
private:
    string file;
protected:
    int programCounter = 0; //?????
public:
    //   Machine(string file);
//    void loadProgramFile();
    virtual void output(Memory &m);
    void displayMenu();
    string getNextInstruction(string first, string second, string third);
    friend class Instruction;
};

class Instruction: public Machine{
private:
    Machine machine;
    Memory memory;
public:
    void setR(Memory &memory1);
    void setMemo(Memory &memory1);
    void execute();
    void Load1(string , string);
    void Load2(string, string);
    void output(Memory &m);
    void Store(string, string);
    void move(string, string);
    void add(string, string, string);
    int jump(string, string , int);
    int halt();

};
#endif //MACHINETASK_MACHINE_H
