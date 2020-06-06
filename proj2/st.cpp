#include "st.hpp"


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