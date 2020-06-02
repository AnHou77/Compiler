#include <iostream>
#include <map>
#include <string>



class SymbolTable{
public:

    SymbolTable();
    void push();
    void pop();
    void insert();
    SymbolTable lookup();
};