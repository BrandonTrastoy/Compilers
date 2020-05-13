//
//  part1.cpp
//  CompilersProgram1
//
//  Created by Brandon Trastoy on 3/5/20.
//  Copyright © 2020 Brandon Trastoy. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
using namespace std;

void program();
void stmtlist();
void stmt();
void assign();
void print();
void expr();
void id();
void number();

int math();

string expression;
int i = 0;

int main()
{
    cout << "Enter A Valid Expression: "; cin >> expression;
    
    program();
    
}

void program() {
    
    stmtlist();
    
    if(expression[i] == '.' && i == (expression.length()-1)) {
        cout << "Parse Successful" << endl;
        math();
    }
    else {
        cout << "Invalid Expression" << endl;
    }
}
void stmtlist() {
    
    stmt();
    
    if(expression[i] == ';') {
        i++;
        stmtlist();
    }
}
void stmt() {
    assign();
    print();
}
void assign() {
    
    id();
    
    if(expression[i] == '=') {
        i++;
        expr();
    }
}
void print() {
    if(expression[i] == '!') {
        i++;
        id();
    }
}
void expr() {
    
    if(expression[i] == '+' || expression[i] == '-'||
       expression[i] == '*' || expression[i] == '/')
    {
        i++;
        expr();
        expr();
    }
    
    id();
    number();
}
void id() {
    
    if(expression[i] == 'a' || expression[i] == 'b' || expression[i] == 'c') {
        i++;
    }
}
void number() {
    
    if((expression[i] >= '0' && expression[i] <= '9')) {
        i++;
    }
}

int math() {
    
    char variables[3] = {'\0', '\0', '\0'}; // stores all vars used
    int values[3] = {0, 0, 0}; // stores all values corresponding to variables
    char varsToPrint[3] = {'\0', '\0', '\0'}; // stores all values to print
    
    for (int x = 0; x < expression.size(); x++) {
        // Stores variables and does some math
        if(expression[x] == 'a' || expression[x] == 'b' || expression[x] == 'c') {
            char temp = expression[x];
            for(int k = 0; k < 3; k++) {
                if(variables[k] == temp || variables[k] == '\0') {
                    variables[k] = temp;
                    k=3; // Close loop when added
                }
            }
            x++;
            if(expression[x] == '=') {
                x++;
                if(expression[x] == 'a' || expression[x] == 'b' || expression[x] == 'c') {
                    if(temp == expression[x]) {
                        //variable cannot reference itself
                        cout << "exception" << endl;
                        return -1;
                    }
                    bool exists = false;
                    int location = 0;
                    
                    for(int j = 0; j < 3; j++) {
                        if(expression[x] == variables[j]) {
                            exists = true;
                            location = j;
                        }
                    }
                    if(exists) {
                        int locationToStore = 0;
                        for(int j = 0; j < 3; j++) {
                            if(variables[j] == '\0' || variables[j] == temp) {
                                variables[j] = temp;
                                locationToStore = j;
                                j = 3; //Close loop clean
                            }
                        }
                        // Stores referenced value
                        values[locationToStore] = values[location];
                    }
                    else {
                        //Tried to reference value that does not exist
                        cout << "exception" << endl;
                        return -1;
                    }
                }
                else if(expression[x] >= '0' && expression[x] <= '9') {
                    int locationToStore = 0;
                    for(int j = 0; j < 3; j++) {
                        if(variables[j] == '\0' || variables[j] == temp) {
                            variables[j] = temp;
                            locationToStore = j;
                            j = 3; //Close loop clean
                        }
                    }
                    // converts char to num and stores
                    values[locationToStore] = expression[x] - '0';
                }
                else if(expression[x] == '+' || expression[x] == '-' ||
                        expression[x] == '*' || expression[x] == '/')
                {
                    char symbol[expression.size()];
                    char tempValues[expression.size()];
                    int tempNums[expression.size()];
                    int z = 0;
                    while(expression[x] == '+' || expression[x] == '-' ||
                          expression[x] == '*' || expression[x] == '/')
                    {
                        symbol[z] = expression[x];
                        z++;
                        x++;
                    }
                    
                    // Stores values in tempValues
                    for(int k = 0; k < z+1; k++) {
                        tempValues[k] = expression[x];
                        x++;
                    }
                    
                    // Stores values in tempNums
                    for(int k = 0; k < z+1; k++) {
                        if(tempValues[k] >= '0' && tempValues[k] <= '9') {
                            tempNums[k] = (tempValues[k] - '0');
                        }
                        else {
                            for(int l = 0; l < 3; l++) {
                                if(tempValues[k] == variables[l]) {
                                    tempNums[k] = values[l];
                                    l = 3; // Clean close
                                }
                            }
                        }
                    }
                    
                    int total = tempNums[0];
                    // calculates expression for variable
                    for(int k = z-1, l = 1; k >= 0 && l < z+1; k--, l++) {
                        if(symbol[k] == '+') {
                            total = total + tempNums[l];
                        }
                        else if(symbol[k] == '-') {
                            total = total - tempNums[l];
                        }
                        else if(symbol[k] == '*') {
                            total = total * tempNums[l];
                        }
                        else {
                            //Check for division by 0
                            if(tempNums[l] == 0) {
                                cout << "Division by zero" << endl;
                                return -1;
                            }
                            total = total / tempNums[l];
                        }
                    }
                    
                    //Store total in variable
                    for(int k = 0; k < 3; k++) {
                        if(variables[k] == temp) {
                            values[k] = total;
                            k=3;
                        }
                    }
                }
                else {
                    cout << expression[x];
                }
            }
        }
        
        // Store variables to print
        else if(expression[x] == '!') {
            x++;
            for(int k = 0; k < 3; k++) {
                if(varsToPrint[k] == expression[x] || varsToPrint[k] == '\0') {
                    varsToPrint[k] = expression[x];
                    k=3;
                }
            }
        }
    }
    
    // Print all values that are stored
    for(int k = 0; k < 3; k++) {
        for(int j = 0; j < 3; j++) {
            if(variables[j] == varsToPrint[k] && varsToPrint[k] != '\0') {
                cout << varsToPrint[k] << "=" << values[j] << endl;
                j=3;
            }
        }
    }
    
    return 0;
}


