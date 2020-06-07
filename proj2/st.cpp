#include "st.h"


bool SymbolTable::checkIsExist(string name){
    if (table.find(name) != table.end()){
        return true;
    }
    return false;
}

int SymbolTable::insert(string name, IDType id_type){
    if (checkIsExist(name)) {
        return -1;
    }
    IDDetail *tmp = new IDDetail;
    tmp->type = id_type;
    tmp->name = name;
    table[name] = tmp;
    return 1;
}

int SymbolTable::insert(string name, IDType id_type, ValueDetail *val){
    if (checkIsExist(name)) {
        return -1;
    }
    IDDetail *tmp = new IDDetail;
    tmp->type = id_type;
    tmp->name = name;
    tmp->val = val;
    tmp->needInit = false;
    table[name] = tmp;
    return 1;
}

int SymbolTable::insert(string name, IDType id_type, ValueType val_type){
    if (checkIsExist(name)) {
        return -1;
    }
    IDDetail *tmp = new IDDetail;
    tmp->type = id_type;
    tmp->name = name;
    tmp->val->type = val_type;
    table[name] = tmp;
    return 1;
}

int SymbolTable::insert(string name, IDType id_type, ValueType arr_type, int size){
    if (checkIsExist(name)) {
        return -1;
    }
    IDDetail *tmp = new IDDetail;
    tmp->type = id_type;
    tmp->name = name;
    tmp->val = NULL;
    
    // initial array
    tmp->arrType = arr_type;
    tmp->arrLength = size;
    for (int i = 0; i < size; i++){
        tmp->arr_val.push_back(new ValueDetail());
    }
    table[name] = tmp;
    return 1;
}

IDDetail* SymbolTable::lookup(string name){
    if (checkIsExist(name)){
        return table[name];
    }
    return NULL;
}

void SymbolTable::dump(){
    if (!table.empty()){
        for (map<string, IDDetail *>::iterator iter = table.begin(); iter != table.end(); iter++)
        {
            cout << "ID: " << iter->first << "\tType: " << getIDTypeStr(iter->second->type);
            if (iter->second->type == CONST_type || iter->second->type == VAR_type){
                cout << "\t ValueType:" << getVALTypeStr(iter->second->val->type);
            }
            cout << endl;
        }
        cout << "------------------------------------------------" << endl;
    }
}

void SymbolTableS::push(){
    table_vec.push_back(SymbolTable());
    ++first;
}

bool SymbolTableS::pop(){
    if (table_vec.size() == 0){
        return false;
    }
    table_vec.pop_back();
    --first;
    return true;
}

IDDetail* SymbolTableS::lookup(string name){
    for (int i = 0; i <= first ; i++){
        IDDetail *tmp = table_vec[i].lookup(name);
        if (tmp != NULL){
            return tmp;
        }
    }
    return NULL;
}

void SymbolTableS::dump(){
    if(first >= 0){
        cout << "=================Symbol Tables=================" << endl;
        for (int i = 0; i <= first; i++){
            cout << "---------------------------------(" << i << ")" << endl;
            table_vec[i].dump();
        }
    }
}

ValueDetail *INTconst(int val){
    ValueDetail *tmp = new ValueDetail();
    tmp->type = INT_type;
    tmp->intValue = val;
    return tmp;
}
ValueDetail *FLOATconst(float val){
    ValueDetail *tmp = new ValueDetail();
    tmp->type = FLOAT_type;
    tmp->floatValue = val;
    return tmp;
}
ValueDetail *CHARconst(char val){
    ValueDetail *tmp = new ValueDetail();
    tmp->type = CHAR_type;
    tmp->charValue = val;
    return tmp;
}
ValueDetail *STRINGconst(string* val){
    ValueDetail *tmp = new ValueDetail();
    tmp->type = STRING_type;
    tmp->stringValue = val;
    return tmp;
}
ValueDetail *BOOLconst(bool val){
    ValueDetail *tmp = new ValueDetail();
    tmp->type = BOOL_type;
    tmp->boolValue = val;
    return tmp;
}

ValueDetail* operator + (ValueDetail& left, const ValueDetail& right){
    ValueDetail* tmp = new ValueDetail();
    tmp->type = left.type;
    if(tmp->type == INT_type){
        tmp->intValue = left.intValue + right.intValue;
    }
    else if(tmp->type == FLOAT_type){
        tmp->floatValue = left.floatValue + right.floatValue;
    }
    return tmp;
}

ValueDetail* operator - (ValueDetail& left, const ValueDetail& right){
    ValueDetail* tmp = new ValueDetail();
    tmp->type = left.type;
    if(tmp->type == INT_type){
        tmp->intValue = left.intValue - right.intValue;
    }
    else if(tmp->type == FLOAT_type){
        tmp->floatValue = left.floatValue - right.floatValue;
    }
    return tmp;
}

ValueDetail* operator * (ValueDetail& left, const ValueDetail& right){
    ValueDetail* tmp = new ValueDetail();
    tmp->type = left.type;
    if(tmp->type == INT_type){
        tmp->intValue = left.intValue * right.intValue;
    }
    else if(tmp->type == FLOAT_type){
        tmp->floatValue = left.floatValue * right.floatValue;
    }
    return tmp;
}

ValueDetail* operator / (ValueDetail& left, const ValueDetail& right){
    ValueDetail* tmp = new ValueDetail();
    tmp->type = left.type;
    if(tmp->type == INT_type){
        tmp->intValue = left.intValue / right.intValue;
    }
    else if(tmp->type == FLOAT_type){
        tmp->floatValue = left.floatValue / right.floatValue;
    }
    return tmp;
}

ValueDetail* operator > (ValueDetail& left, const ValueDetail& right){
    ValueDetail* tmp = new ValueDetail();
    tmp->type = BOOL_type;
    if(left.type == INT_type){
        if(left.intValue > right.intValue){
            tmp->boolValue = true;
        }
        else{
            tmp->boolValue = false;
        }
    }
    else if(left.type == FLOAT_type){
        if(left.floatValue > right.floatValue){
            tmp->boolValue = true;
        }
        else{
            tmp->boolValue = false;
        }
    }
    return tmp;
}

ValueDetail* operator < (ValueDetail& left, const ValueDetail& right){
    ValueDetail* tmp = new ValueDetail();
    tmp->type = BOOL_type;
    if(left.type == INT_type){
        if(left.intValue < right.intValue){
            tmp->boolValue = true;
        }
        else{
            tmp->boolValue = false;
        }
    }
    else if(left.type == FLOAT_type){
        if(left.floatValue < right.floatValue){
            tmp->boolValue = true;
        }
        else{
            tmp->boolValue = false;
        }
    }
    return tmp;
}

ValueDetail* operator >= (ValueDetail& left, const ValueDetail& right){
    ValueDetail* tmp = new ValueDetail();
    tmp->type = BOOL_type;
    if(left.type == INT_type){
        if(left.intValue >= right.intValue){
            tmp->boolValue = true;
        }
        else{
            tmp->boolValue = false;
        }
    }
    else if(left.type == FLOAT_type){
        if(left.floatValue >= right.floatValue){
            tmp->boolValue = true;
        }
        else{
            tmp->boolValue = false;
        }
    }
    return tmp;
}

ValueDetail* operator <= (ValueDetail& left, const ValueDetail& right){
    ValueDetail* tmp = new ValueDetail();
    tmp->type = BOOL_type;
    if(left.type == INT_type){
        if(left.intValue <= right.intValue){
            tmp->boolValue = true;
        }
        else{
            tmp->boolValue = false;
        }
    }
    else if(left.type == FLOAT_type){
        if(left.floatValue <= right.floatValue){
            tmp->boolValue = true;
        }
        else{
            tmp->boolValue = false;
        }
    }
    return tmp;
}

ValueDetail* operator == (ValueDetail& left, const ValueDetail& right){
    ValueDetail* tmp = new ValueDetail();
    tmp->type = BOOL_type;
    if(left.type == INT_type){
        if(left.intValue == right.intValue){
            tmp->boolValue = true;
        }
        else{
            tmp->boolValue = false;
        }
    }
    else if(left.type == FLOAT_type){
        if(left.floatValue == right.floatValue){
            tmp->boolValue = true;
        }
        else{
            tmp->boolValue = false;
        }
    }
    else if(left.type == CHAR_type){
        if(left.charValue == right.charValue){
            tmp->boolValue = true;
        }
        else{
            tmp->boolValue = false;
        }
    }
    else if(left.type == STRING_type){
        if(left.stringValue == right.stringValue){
            tmp->boolValue = true;
        }
        else{
            tmp->boolValue = false;
        }
    }
    else if(left.type == BOOL_type){
        if(left.boolValue == right.boolValue){
            tmp->boolValue = true;
        }
        else{
            tmp->boolValue = false;
        }
    }
    return tmp;
}

ValueDetail* operator != (ValueDetail& left, const ValueDetail& right){
    ValueDetail* tmp = new ValueDetail();
    tmp->type = BOOL_type;
    if(left.type == INT_type){
        if(left.intValue != right.intValue){
            tmp->boolValue = true;
        }
        else{
            tmp->boolValue = false;
        }
    }
    else if(left.type == FLOAT_type){
        if(left.floatValue != right.floatValue){
            tmp->boolValue = true;
        }
        else{
            tmp->boolValue = false;
        }
    }
    else if(left.type == CHAR_type){
        if(left.charValue != right.charValue){
            tmp->boolValue = true;
        }
        else{
            tmp->boolValue = false;
        }
    }
    else if(left.type == STRING_type){
        if(left.stringValue != right.stringValue){
            tmp->boolValue = true;
        }
        else{
            tmp->boolValue = false;
        }
    }
    else if(left.type == BOOL_type){
        if(left.boolValue != right.boolValue){
            tmp->boolValue = true;
        }
        else{
            tmp->boolValue = false;
        }
    }
    return tmp;
}

string getIDTypeStr(IDType type){
    switch (type)
    {
    case CONST_type:
        return "Constant_ID";
    case VAR_type:
        return "Variable_ID";
    case ARRAY_type:
        return "Array_ID";
    case FUNC_type:
        return "Function_ID";
    case OBJECT_type:
        return "Object_ID";
    default:
        return "Undefined_Type_ID";
    }
}
string getVALTypeStr(ValueType type){
    switch (type)
    {
    case INT_type:
        return "Integer_Value";
    case FLOAT_type:
        return "float_Value";
    case CHAR_type:
        return "Char_Value";
    case STRING_type:
        return "String_Value";
    case BOOL_type:
        return "Boolean_Value";
    default:
        return "Undefined_Type_Value";
    }
}