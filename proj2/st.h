#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

enum ValueType{
    INT_type,
    FLOAT_type,
    CHAR_type,
    STRING_type,
    BOOL_type,
    VAL_UNDEF_type,
};

enum IDType{
    CONST_type,
    VAR_type,
    ARRAY_type,
    FUNC_type,
    OBJECT_type,
    ID_UNDEF_type,
};

struct ValueDetail{
    ValueType type = VAL_UNDEF_type;
    
    int intValue = 0;
    float floatValue = 0;
    char charValue = '\0';
    string *stringValue = new string();
    bool boolValue = false;

    string arg_name = "";
};

struct IDDetail{
    IDType type = ID_UNDEF_type;
    int idx = -1;

    string name = "";
    ValueDetail *val = NULL;

    vector<ValueDetail*> arr_val;
    ValueType arrType = VAL_UNDEF_type;
    int arrLength = 0;

    ValueType returnType = VAL_UNDEF_type;

    vector<ValueDetail*> arg_val;

    bool needInit = true;
};

class SymbolTable{
public:
    SymbolTable(){idx = 0;};
    
    int idx;
    map<string, IDDetail*> table;

    int insert(string, IDType);
    int insert(string, IDType, ValueDetail*);
    int insert(string, IDType, ValueType);
    int insert(string, IDType, ValueType, int);

    IDDetail *lookup(string);
    bool checkIsExist(string);
};

class SymbolTableS{
public:
    SymbolTableS(){
        first = -1;  
        push();
    };
    
    vector<SymbolTable> table_vec;
    int first;

    void push();
    bool pop();

    IDDetail *lookup(string);

    void dump();
};

ValueDetail *INTconst(int);
ValueDetail *FLOATconst(float);
ValueDetail *CHARconst(char);
ValueDetail *STRINGconst(string*);
ValueDetail *BOOLconst(bool);

ValueDetail* operator + (ValueDetail&, const ValueDetail&);
ValueDetail* operator - (ValueDetail&, const ValueDetail&);
ValueDetail* operator * (ValueDetail&, const ValueDetail&);
ValueDetail* operator / (ValueDetail&, const ValueDetail&);
ValueDetail* operator > (ValueDetail&, const ValueDetail&);
ValueDetail* operator < (ValueDetail&, const ValueDetail&);
ValueDetail* operator >= (ValueDetail&, const ValueDetail&);
ValueDetail* operator <= (ValueDetail&, const ValueDetail&);
ValueDetail* operator == (ValueDetail&, const ValueDetail&);
ValueDetail* operator != (ValueDetail&, const ValueDetail&);

