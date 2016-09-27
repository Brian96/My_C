//
//  main.cpp
//  lab2
//
//  Created by mac on 2016-09-24.
//  Copyright © 2016 mac. All rights reserved.
//

#define MIN_NODE_NUMBER 0
#define MAX_NODE_NUMBER 5000
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

//all commands used
void insertR(string line);
void modifyR(string line);
void printR(string line);
void printNode(string line);
void deleteR(string line);
//all errors can be met
void errCmd();
void errArg();
void negResistor();
void outRange(int index);
void errAll();
void sameTerminal(int index);
void tooMany();
void tooFew();
//wordCount counts how many arguments in the line
int wordCount(string line);


int main() {
    string line, cmd;
    cout << "> ";
    getline (cin, line);
    while (!cin.eof()) {
        stringstream ss (line);
        ss >> cmd;
        if (cmd == "insertR") { //parse an insert command
            insertR(line);
        }
        else if (cmd == "modifyR") {    //parse a modify command
            modifyR(line);
        }
        else if (cmd == "printR"){  //parse a print command
            printR(line);
        }
        else if (cmd == "printNode"){   //parse a printNode command
            printNode(line);
        }
        else if (cmd == "deleteR"){ //parse a delete command
            deleteR(line);
        }
        else {  //parse an invalid command
            errCmd();
        }
        cout << "> ";
        getline (cin, line);
    } // End input loop until EOF.
    return 0;
}

void errCmd(){
    cout << "Error: invalid command" << endl;
}

void errArg(){
    cout << "Error: invalid argument" << endl;
}

void negResistor(){
    cout << "Error: negative resistance" << endl;
}

void outRange(int index){
    cout << "Error: node " << index << " is out of permitted range " << MIN_NODE_NUMBER << "-" << MAX_NODE_NUMBER << endl;
}

void errAll(){
    cout << "Error: resistor name cannot be the keyword \"all\"" << endl;
}

void sameTerminal(int index){
    cout << "Error: both terminals of resistor connect to node " << index << endl;
}

void tooMany(){
    cout << "Error: too many arguments" << endl;
}

void tooFew(){
    cout << "Error: too few arguments" << endl;
}

void insertR(string line){
    int num = wordCount(line);
    string cmd;
    stringstream ss(line);
    ss >> cmd;
    string name;
    ss >> name;
    if (name == "all"){
        errAll();
        return;
    }
    if (ss.fail()){
        tooFew();
        return;
    }
    double ohm;
    ss >> ohm;
    if(ohm < 0){
        negResistor();
        return;
    }
    if (ss.fail()){
        ss.clear();
        string a;
        ss >> a;
        if (ss.fail()){
            tooFew();
            return;
        }
        errArg();
        return;
    }
    int node1, node2;
    ss >> node1;
    if (ss.fail()){
        ss.clear();
        string a;
        ss >> a;
        if (ss.fail()){
            tooFew();
            return;
        }
        errArg();
        return;
    }
    if (node1 < MIN_NODE_NUMBER || node1 > MAX_NODE_NUMBER){
        outRange(node1);
        return;
    }
    ss >> node2;
    if (ss.fail()){
        ss.clear();
        string a;
        ss >> a;
        if (ss.fail()){
            tooFew();
            return;
        }
        errArg();
        return;
    }
    if (node2 < MIN_NODE_NUMBER || node2 > MAX_NODE_NUMBER){
        outRange(node2);
        return;
    }
    if (node1 == node2){
        sameTerminal(node1);
        return;
    }
    if (num > 5){
        tooMany();
        return;
    }
    cout << "Inserted: resistor " << name << " ";
    cout << setprecision(2) << fixed << ohm << " Ohms ";
    cout << node1 << " -> " << node2 << endl;
}


void modifyR(string line){
    int num = wordCount(line);
    string cmd;
    stringstream ss(line);
    ss >> cmd;
    string name;
    ss >> name;
    if (name == "all"){
        errAll();
        return;
    }
    double ohm;
    ss >> ohm;
    if (ss.fail()){
        ss.clear();
        string check;
        ss >> check;
        if (ss.fail()){
            tooFew();
            return;
        }
        errArg();
        return;
    }
    if(ohm < 0){
        negResistor();
        return;
    }
    if (num > 3){
        tooMany();
        return;
    }
    else if (num < 3){
        tooFew();
        return;
    }
    cout << "Modified: resistor " << name << " to " << setprecision(2) << fixed << ohm << " Ohms" << endl;
}

void printR(string line){
    int num = wordCount(line);
    string cmd;
    stringstream ss(line);
    ss >> cmd;
    string name;
    ss >> name;
    if (num > 2){
        tooMany();
        return;
    }
    if (num < 2){
        tooFew();
        return;
    }
    if (name == "all"){
        cout << "Print: all resistors" << endl;
    }
    else{
        cout << "Print: resistor " << name << endl;
    }
}

void printNode(string line){
    int num = wordCount(line);
    string cmd;
    stringstream ss(line);
    ss >> cmd;
    bool pickNode = true;
    int node;
    string all;
    ss >> node;
    if (ss.fail()){
        ss.clear();
        ss >> all;
        if (ss.fail()){
            tooFew();
            return;
        }
        else if (all != "all"){
            errArg();
            return;
        }
        pickNode = false;
    }
    else{
        if (node > MAX_NODE_NUMBER){
            outRange(node);
            return;
        }
        if (node < MIN_NODE_NUMBER){
            outRange(node);
            return;
        }
    }
    if (num > 2){
        tooMany();
        return;
    }
    if (num < 2){
        tooFew();
        return;
    }
    if (pickNode){
        cout << "Print: node " << node << endl;
    }
    else {
        cout << "Print: all nodes" << endl;
    }
    
}

void deleteR(string line){
    int num = wordCount(line);
    string cmd;
    stringstream ss(line);
    ss >> cmd;
    string name;
    ss >> name;
    if (num > 2){
        tooMany();
        return;
    }
    if (num < 2){
        tooFew();
        return;
    }
    if (name == "all"){
        cout << "Deleted: all resistors" << endl;
    }
    else{
        cout << "Deleted: resistor " << name << endl;
    }
}

int wordCount(string line){
    string s;
    int number = 0;
    stringstream ss(line);
    while (ss >> s) number++;
    return number;
}
