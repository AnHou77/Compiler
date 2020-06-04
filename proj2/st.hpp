#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

enum ValueType{
    INTtype,
    FLOATtype,
    CHARtype,
    STRINGtype,
    BOOLtype,
};

struct ValueDetail{
    int intValue = 0;
    float floatValue = 0;
    char charValue = '\0';
    string *stringValue = new string();
    bool boolValue = false;
};

class SymbolTable{
public:

    SymbolTable();
    void push();
    void pop();
    void insert();
    SymbolTable lookup();
    string s;
};