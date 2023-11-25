#ifndef MACHINETASK_MACHINE_H
#define MACHINETASK_MACHINE_H

#include <bits/stdc++.h>

using namespace std;

class Register{
private:
    vector<string>R;
public:
    Register();
    friend class Machine;
    friend class Instruction;
};

class Memory {
private:
    // string file;
    vector<string>memo;
public:
    Memory();
    Memory(string);
//    void setMemorySize();
//    void setRSize();
    friend class Machine;
    friend class Instruction;
};

class Machine {
private:
    string file;
    Memory memory;
    Register R;
protected:
    int programCounter = 0; //?????
public:
    //   Machine(string file);
//    void loadProgramFile();
    virtual void output(Memory &m, Register &r);
    void displayMenu();
    string getNextInstruction(const string &first,const string &second,const string &third);
    friend class Instruction;
};

class Instruction: public Machine{
private:
    Machine machine;
    Memory memory;
    Register regi;
public:
    void execute();
    void setR(Register &reg);
    void setMemo(Memory &memory1);
    void Load1(const string& , const string&);
    void Load2(const string&, const string&);
    void output(Memory &m, Register &r);
    void Store(const string&, const string&);
    void move(const string&, const string&);
    void add(const string&, const string&, const string&);
    int jump(const string&, const string& , int);

};
#endif //MACHINETASK_MACHINE_H
