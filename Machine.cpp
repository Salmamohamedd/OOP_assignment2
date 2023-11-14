#include <bits/stdc++.h>
#include "Machine.h"

Memory::Memory(string filee) {
    filee = "Instruction.txt";
    ifstream file(filee);
    string line;

    while (getline(file, line)) {
        string first = "", second = "", third = "";
        istringstream iss(line);
        if (!(iss >> first >> second >> third)) {
            break;
        }

        string str = "", str2 = "";
        str = str + first[2] + second[2];
        str2 = str2 + third[2] + third[3];
        memo.push_back(str);
        memo.push_back(str2);
    }

    file.close();

    R = {{"00"}};
}

string Machine::getNextInstruction(string first, string second, string third) {
    return to_string(first[2] + second[2] + third[2] + third[3]);
}


void Instruction::execute() {
    vector<string> instruction;
    ifstream file("Instruction.txt");
    string line;
    while (getline(file, line)) {
        string first = "", second = "", third = "";
        istringstream iss(line);
        if (!(iss >> first >> second >> third)) {
            break;
        }
        instruction.push_back(M.getNextInstruction(first, second, third));
    }
    file.close();

    for (int i = 0; i < instruction.size(); ++i) {
        char inst = instruction[i][0];
        string r = "", a = ""; //register and address
        r = r + instruction[i][1];
        a = a + instruction[i][2] + instruction[i][3];

        switch (inst) {
            case '1':
                Load1(r, a);
        }
    }
}

void Instruction::Load1(string reg, string address) {
    int index_reg = stoi(reg, nullptr, 16);
    int index_address = stoi(address, nullptr, 16);

    //R (second in string instruction)
    //store the value of address (address is the index, convert address into decimal first)
    //set change in register, the address and value remain the same

}

//void Machine::loadProgramFile() {
//    ifstream file("Instruction.txt");
//    string line;
//    while (getline(file, line)) {
//        string first = "", second = "", third = "";
//        istringstream iss(line);
//        if (!(iss >> first >> second >> third)) {
//            break;
//        }
//        string instruction = this->getNextInstruction(first , second , third);
//    }
//    file.close();
//}

