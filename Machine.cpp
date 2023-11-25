#include <bits/stdc++.h>
#include "Machine.h"

Memory::Memory() : memo(256){
    for (int j = 0; j < memo.size(); ++j) {
        memo[j] = "00";
    }
    string filee = "Instruction.txt";
    ifstream file(filee);
    string line;
    int i = 0;

    while (getline(file, line)) {
        string first = "", second = "", third = "";
        istringstream iss(line);
        if (!(iss >> first >> second >> third)) {
            break;
        }

        string str = "", str2 = "";
        str = str + first[2] + second[2];
        str2 = str2 + third[2] + third[3];
        memo[i] = str;
        memo[++i] = str2;
        ++i;
    }

    file.close();

}

Memory::Memory(string filee) :memo(256) {
        for (int j = 0; j < memo.size(); ++j) {
            memo[j] = "00";
        }
        ifstream file(filee);
        string line;
        int i = 0;

        while (getline(file, line)) {
            string first = "", second = "", third = "";
            istringstream iss(line);
            if (!(iss >> first >> second >> third)) {
                break;
            }

            string str = "", str2 = "";
            str = str + first[2] + second[2];
            str2 = str2 + third[2] + third[3];
            memo[i] = str;
            memo[++i] = str2;
            ++i;
        }

        file.close();

}

string Machine::getNextInstruction(const string &first, const string &second, const string &third) {
    string instruction = first.substr(2, 1) + second.substr(2, 1) + third.substr(2, 1) + third.substr(3, 1);
    return instruction;
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
        instruction.emplace_back(machine.getNextInstruction(first, second, third));
    }
    file.close();

    for (int i = 0; i < instruction.size(); ++i) {
        programCounter += 2;
        char inst = instruction[i][0];
        string r = "", a = ""; //register and address
        r = r + instruction[i][1];
        a = a + instruction[i][2] + instruction[i][3];

        if (inst == '1') {
            Load1(r, a);
        } else if (inst == '2') {
            Load2(r, a);
        } else if (inst == '3') {
            if (a == "00") {
                int index_reg = stoi(r, nullptr, 16);
                cout << regi.R[index_reg] << "\n";
            } else
                Store(r, a);
        } else if (inst == '4') {
            string rr = "", ss = "";
            rr = rr + instruction[i][2];
            ss = ss + instruction[i][3];
            move(rr, ss);
        } else if (inst == '5') {
            string rr = "", ss = "";
            rr = rr + instruction[i][2];
            ss = ss + instruction[i][3];
            add(r, rr, ss);
        } else if (inst == 'B') {
            int index = jump(r, a, i);
            if (index == i) {
                continue;
            } else {
                i = index - 1;
                programCounter = index * 2;
            }

        } else if (inst == 'C') {
            return;
        }
    }
}

void Instruction::Load1(const string &reg, const string &address) {
    int index_reg = stoi(reg, nullptr, 16);
    int index_address = stoi(address, nullptr, 16);
    regi.R[index_reg] = memory.memo[index_address];

}

void Instruction::Load2(const string &reg, const string &address) {
    int index_reg = stoi(reg, nullptr, 16);
    regi.R[index_reg] = address;
}

void Instruction::Store(const string &reg, const string &address) {
    int index_reg = stoi(reg, nullptr, 16);
    int index_address = stoi(address, nullptr, 16);
    memory.memo[index_address] = regi.R[index_reg];
}

void Instruction::move(const string& R, const string& S) {
    int index_reg1 = stoi(R, nullptr, 16);
    int index_reg2 = stoi(S, nullptr, 16);
    regi.R[index_reg2] = regi.R[index_reg1];
//    regi.R[index_reg1] = "00";
}

void Instruction::add(const string &R, const string &S, const string &T) {
    int index_reg = stoi(R, nullptr, 16);
    int index_reg1 = stoi(S, nullptr, 16);
    int index_reg2 = stoi(T, nullptr, 16);
    string patternS = regi.R[index_reg1], patternT = regi.R[index_reg2];
    string binaryS = "";
    char c;
    for (int j = 0; j < patternS.length(); j++) {
        c = patternS[j];
        if (c >= '0' && c <= '9') {
            binaryS += bitset<4>(c - '0').to_string();
        } else if (c >= 'A' && c <= 'F') {
            binaryS += bitset<4>(c - 'A' + 10).to_string();
        } else if (c >= 'a' && c <= 'f') {
            binaryS += bitset<4>(c - 'a' + 10).to_string();
        }
    }

    string binaryT = "";
    for (int i = 0; i < patternT.length(); i++) {
        c = patternT[i];
        if (c >= '0' && c <= '9') {
            binaryT += bitset<4>(c - '0').to_string();
        } else if (c >= 'A' && c <= 'F') {
            binaryT += bitset<4>(c - 'A' + 10).to_string();
        } else if (c >= 'a' && c <= 'f') {
            binaryT += bitset<4>(c - 'a' + 10).to_string();
        }
    }
    string sum = "";
    int len1, len2, i, j, ds = 0;
    len1 = binaryS.size();
    len2 = binaryT.size();
    i = len1 - 1;
    j = len2 - 1;
    while (i >= 0 || j >= 0 || ds == 1) {
        ds = ds + ((i >= 0) ? binaryS[i] - '0' : 0);
        ds = ds + ((j >= 0) ? binaryT[j] - '0' : 0);
        sum = char(ds % 2 + '0') + sum;
        ds = ds / 2;
        i--;
        j--;
    }

    string hexa = "";
    for (int i = 0; i < sum.length(); i += 4) {
        string b = sum.substr(i, 4);
        c = (char) stoi(b, nullptr, 2);
        if (c >= 10 && c <= 15) {
            hexa += char(c - 10 + 'A');
        } else {
            hexa += to_string(c);
        }
    }
    regi.R[index_reg] = hexa;

}

int Instruction::jump(const string& reg, const string& address, int currentIndex) {
    int index_reg = stoi(reg, nullptr, 16); //register index in registers //01
    int index_address = stoi(address, nullptr, 16); //address in memory //10 index 16(val)
    if (regi.R[index_reg] == regi.R[0]) {
        int jump_index = (index_address / 2); //0xB 0x1 0x10
        return jump_index;
    } else {
        return currentIndex;
    }
}

void Instruction::setR(Register &reg) {
    for (int i = 0; i < 16; ++i) {
        reg.R[i] = regi.R[i];
    }

}

void Instruction::setMemo(Memory &memory1) {
    for (int i = 0; i < 256; ++i) {
        memory1.memo[i] = memory.memo[i];
    }
}

void Machine::output(Memory &memory, Register &register1) {
    cout << "Memory: " << '\n';
    for (int i = 0; i < memory.memo.size(); ++i) {
        cout << memory.memo[i] << '\n';
    }
    cout << "Registers: " << '\n';
    for (int i = 0; i < 16; ++i) {
        cout << register1.R[i] << '\n';
    }
    cout<<"Program Counter: "<<hex<< programCounter <<'\n';
}

void Machine::displayMenu() {
    int n;
    Instruction I;
    cout << "What would you like to choose:\n"
            "(1) Load Program File\n"
            "(2) Run Program File\n"
            "(3) Print contents of Registers and Memory addresses\n"
            "(4) Exit: ";
    while (cin >> n) {
        if (n == 1) {
            cout << "Enter file name: ";
            string file;
            cin >> file;
            Memory memory1(file);
        } else if (n == 2) {
            I.execute();
        } else if (n == 3){
            I.output(memory, R);
        } else if (n == 4){
            return;
        } else{
            cout << "Enter a valid number: ";
        }
        cout << "What would you like to choose:\n"
                "(1) Load Program File\n"
                "(2) Run Program File\n"
                "(3) Print contents of Registers and Memory addresses\n"
                "(4) Exit: ";

    }
}

void Instruction::output(Memory &memory, Register &reg) {
    setR(reg);
    setMemo(memory);
    cout << "Memory: " << '\n';
    for (int i = 0; i < memory.memo.size(); ++i) {
        cout << memory.memo[i] << '\n';
    }
    cout << "Registers: " << '\n';
    for (int i = 0; i < 16; ++i) {
        cout << regi.R[i] << '\n';
    }
    cout<<"Program Counter: "<<hex<< programCounter <<'\n';
}

Register::Register() : R(16){
    for (int j = 0; j < R.size(); ++j) {
        R[j] = "00";
    }
}
