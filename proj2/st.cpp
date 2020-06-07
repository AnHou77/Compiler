#include "st.h"


bool SymbolTable::checkIsExist(string name){
    if (table.find(name) != table.end()){
        return true;
    }
    return false;
}

int SymbolTable::insert(string name, IDType type){
    if (checkIsExist(name)) {
        return -1;
    }
    table[name]->type = type;
    table[name]->idx = idx;
    idx++;
    table[name]->name = name;
    return idx;
}

int SymbolTable::insert(string name, IDType type, ValueDetail *val){
    if (checkIsExist(name)) {
        return -1;
    }
    table[name]->type = type;
    table[name]->idx = idx;
    idx++;
    table[name]->name = name;
    table[name]->val = val;
    table[name]->needInit = false;
    return idx;
}

int SymbolTable::insert(string name, IDType id_type, ValueType val_type){
    if (checkIsExist(name)) {
        return -1;
    }
    table[name]->type = id_type;
    table[name]->idx = idx;
    idx++;
    table[name]->name = name;
    table[name]->val->type = val_type;
    return idx;
}

int SymbolTable::insert(string name, IDType id_type, ValueType arr_type, int size){
    if (checkIsExist(name)) {
        return -1;
    }
    
    table[name]->type = id_type;
    table[name]->idx = idx;
    idx++;
    table[name]->name = name;
    table[name]->val = NULL;
    
    // initial array
    table[name]->arrType = arr_type;
    table[name]->arrLength = size;
    for (int i = 0; i < size; i++){
        table[name]->arr_val.push_back(new ValueDetail());
    }
    
    return idx;
}

IDDetail* SymbolTable::lookup(string name){
    if (checkIsExist(name)){
        return table[name];
    }
    return NULL;
}

void SymbolTableS::push(){
    table_vec.push_back(SymbolTable());
    first++;
}

bool SymbolTableS::pop(){
    if (table_vec.size() == 0){
        return false;
    }
    table_vec.pop_back();
    first--;
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