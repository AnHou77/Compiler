#include "st.h"


bool SymbolTable::checkIsExist(string name){
    if (table.find(name) != table.end()){
        return true;
    }
    return false;
}

/* overloaded insert function for arguments(id_name,id_type) */
int SymbolTable::insert(string name, IDType id_type){
    if (checkIsExist(name)) {
        return -1;
    }
    // initial ID
    IDDetail *tmp = new IDDetail;
    tmp->type = id_type;
    tmp->name = name;
    tmp->val = NULL;
    table[name] = tmp;
    return 1;
}

/* overloaded insert function for arguments(id_name,id_type,id_value) */
int SymbolTable::insert(string name, IDType id_type, ValueDetail *val){
    if (checkIsExist(name)) {
        return -1;
    }
    // initial ID
    IDDetail *tmp = new IDDetail;
    tmp->type = id_type;
    tmp->name = name;
    tmp->val = val;
    tmp->needInit = false;
    table[name] = tmp;
    return 1;
}

/* overloaded insert function for arguments(id_name,id_type,value_type) */
int SymbolTable::insert(string name, IDType id_type, ValueType val_type){
    if (checkIsExist(name)) {
        return -1;
    }
    // initial ID
    IDDetail *tmp = new IDDetail;
    tmp->type = id_type;
    tmp->name = name;
    tmp->val = new ValueDetail();
    tmp->val->type = val_type;
    table[name] = tmp;
    return 1;
}

/* overloaded insert function for arguments(id_name,id_type,array_type,array_size) */
int SymbolTable::insert(string name, IDType id_type, ValueType arr_type, int size){
    if (checkIsExist(name)) {
        return -1;
    }
    // initial ID
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

/* if ID can be found, return it */
IDDetail* SymbolTable::lookup(string name){
    if (checkIsExist(name)){
        return table[name];
    }
    return NULL;
}

/* Dump all ID's infomations */
void SymbolTable::dump(){
    if (!table.empty()){
        for (map<string, IDDetail *>::iterator iter = table.begin(); iter != table.end(); iter++)
        {
            cout << "ID: " << iter->first << "\t Type: " << getIDTypeStr(iter->second->type);
            if (iter->second->type == CONST_type || iter->second->type == VAR_type){
                cout << "\t ValueType:" << getVALTypeStr(iter->second->val->type);
            }
            cout << endl;
        }
    }
}

/* push new table to list */
void SymbolTableS::push(){
    table_vec.push_back(SymbolTable());
    first++;
    cout << "push" << first << endl;
}

/* pop top one table */
void SymbolTableS::pop(){
    table_vec.pop_back();
    first--;
}

/* if ID can be found, return it */
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
        for (int i = 0; i < table_vec.size(); i++){
            cout << "------------------ Table: " << i <<" ------------------" << endl;
            table_vec[i].dump();
            cout << "-----------------------------------------------" << endl;
        }
        cout << "===============================================" << endl;
    }
}

/* initial an integer value */
ValueDetail *INTconst(int val){
    ValueDetail *tmp = new ValueDetail();
    tmp->type = INT_type;
    tmp->intValue = val;
    return tmp;
}
/* initial an float value */
ValueDetail *FLOATconst(float val){
    ValueDetail *tmp = new ValueDetail();
    tmp->type = FLOAT_type;
    tmp->floatValue = val;
    return tmp;
}
/* initial an char value */
ValueDetail *CHARconst(char val){
    ValueDetail *tmp = new ValueDetail();
    tmp->type = CHAR_type;
    tmp->charValue = val;
    return tmp;
}
/* initial an string value */
ValueDetail *STRINGconst(string* val){
    ValueDetail *tmp = new ValueDetail();
    tmp->type = STRING_type;
    tmp->stringValue = val;
    return tmp;
}
/* initial an boolean value */
ValueDetail *BOOLconst(bool val){
    ValueDetail *tmp = new ValueDetail();
    tmp->type = BOOL_type;
    tmp->boolValue = val;
    return tmp;
}
/* overloaded operator + to caculate ValueDetail type */
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
/* overloaded operator - to caculate ValueDetail type */
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
/* overloaded operator * to caculate ValueDetail type */
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
/* overloaded operator / to caculate ValueDetail type */
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
/* overloaded operator > to compare ValueDetail type */
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
/* overloaded operator < to compare ValueDetail type */
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
/* overloaded operator >= to compare ValueDetail type */
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
/* overloaded operator <= to compare ValueDetail type */
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
/* overloaded operator == to compare ValueDetail type */
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
/* overloaded operator != to compare ValueDetail type */
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

/* Just for dump */
string getIDTypeStr(IDType type){
    switch (type)
    {
    case CONST_type:
        return "const";
    case VAR_type:
        return "variable";
    case ARRAY_type:
        return "array";
    case FUNC_type:
        return "function";
    case OBJECT_type:
        return "object";
    default:
        return "undefined";
    }
}

/* Just for dump */
string getVALTypeStr(ValueType type){
    switch (type)
    {
    case INT_type:
        return "int";
    case FLOAT_type:
        return "float";
    case CHAR_type:
        return "char";
    case STRING_type:
        return "java.lang.String";
    /* Boolean in java bytecode -> int */
    case BOOL_type:
        return "int";
    default:
        return "undefined";
    }
}

void genJBOperation(char ops){
    switch (ops)
    {
        case 'n':
            javafile << "\t\tineg" << endl;
            break;
        case '+':
            javafile << "\t\tiadd" << endl;
            break;
        case '-':
            javafile << "\t\tisub" << endl;
            break;
        case '*':
            javafile << "\t\timul" << endl;
            break;
        case '/':
            javafile << "\t\tidiv" << endl;
            break;
        case '&':
            javafile << "\t\tiand" << endl;
            break;
        case '|':
            javafile << "\t\tior" << endl;
            break;
        case '!':
            javafile << "\t\tldc 1" << endl;
            javafile << "\t\tixor" << endl;
            break;
        default:
            break;
    }
}

void genJBLogicOp(int ops){

    javafile << "\t\tisub" << endl;
    int lb1 = labelCnt++;
    cout << "logiclabel++    " << labelCnt <<endl;
    int lb2 = labelCnt++;
    cout << "logiclabel++    " << labelCnt <<endl;
    switch (ops)
    {
    case opLT:
        javafile << "\t\tiflt";
        break;
    case opLE:
        javafile << "\t\tifle";
        break;
    case opGT:
        javafile << "\t\tifgt";
        break;
    case opGE:
        javafile << "\t\tifge";
        break;
    case opEE:
        javafile << "\t\tifeq";
        break;
    case opNE:
        javafile << "\t\tifne";
        break;
    default:
        break;
    }

    javafile << " L" << lb1 << endl;
    javafile << "\t\ticonst_0" << endl;
    javafile << "\t\tgoto L" << lb2 << endl;
    javafile << "\tL" << lb1 << ":" << endl;
    javafile << "\t\ticonst_1" << endl;
    javafile << "\tL" << lb2 << ":" << endl;
}

void IFStart(){
    vector<int> buf;
    ifLabelStack.push_back(buf);
    int top = ifLabelStack.size() - 1;
    ifLabelStack[top].push_back(labelCnt++);
    cout << "label++    " << labelCnt - 1 <<endl;
    ifLabelStack[top].push_back(labelCnt++);
    cout << "label++    " << labelCnt - 1 <<endl;

    cout << "top: " << top << endl;
    buf = ifLabelStack[top];
    int lb = buf[0];
    cout << "top content: " << lb << endl;
    javafile << "\t\tifeq L" << lb << endl;
}

void ELIFStart(){
    int top = ifLabelStack.size() - 1;
    ifLabelStack[top].push_back(labelCnt++);
    cout << "label++    " << labelCnt - 1 <<endl;

    cout << "top: " << top << endl;
    vector<int>buf = ifLabelStack[top];
    int lb = buf[0];
    cout << "top content: " << lb << endl;
    javafile << "\t\tifeq L" << lb << endl;
}

void IFEnd(){
    int top = ifLabelStack.size() - 1;
    vector<int> buf = ifLabelStack[top];

    int lb1 = buf[0];
    if(buf.size() == 2){
        int lb2 = buf[1];
        javafile << "\tL" << lb2 << ":" << endl;
        javafile << "\t\tgoto L" << lb1 << endl;
    }

    javafile << "\tL" << lb1 << ":" << endl;
    cout << "IFEND: label1<" << lb1 << ",labe12<" << lb1+1 << endl;
    ifLabelStack.pop_back();
}

void ELSEStart(){
    int top = ifLabelStack.size() - 1;
    vector<int> buf = ifLabelStack[top];

    int lb = buf[0];
    javafile << "\tL" << lb << ":" << endl;
}

void ELSEEnd(){
    int top = ifLabelStack.size() - 1;
    vector<int> buf = ifLabelStack[top];

    int lb = buf[buf.size() - 1];
    buf.pop_back();
    ifLabelStack[top] = buf;
    
    javafile << "\tL" << lb << ":" << endl;

    ifLabelStack.pop_back();
}

void IFScope(){
    int top = ifLabelStack.size() - 1;
    vector<int> buf = ifLabelStack[top];

    int lb = buf[buf.size() - 1];
    javafile << "\t\tgoto L" << lb << endl;
}

void WHILEStart(){
    vector<int> buf;
    
    buf.push_back(labelCnt++);

    whileLabelStack.push_back(buf);

    int top = whileLabelStack.size() - 1;

    buf = whileLabelStack[top];

    int lb = buf[0];

    javafile << "\t\tgoto L" << lb << endl;
    javafile << "\tL" << lb << ":" << endl;
}
void WHILEBeforeScope(){
    vector<int> tmp;
    
    tmp.push_back(labelCnt++);
    tmp.push_back(labelCnt++);

    whileLabelStack.push_back(tmp);

    int top = whileLabelStack.size() - 1;

    vector<int> buf = whileLabelStack[top];

    int lb1 = buf[buf.size() - 2];
    int lb2 = buf[buf.size() - 1];

    javafile << "\t\tifeq L" << lb1 << endl;
    javafile << "\t\tgoto L" << lb2 << endl;
    javafile << "\tL" << lb1 << ":" << endl;
}

void WHILEScope(){
    int top = whileLabelStack.size() - 1;

    vector<int> buf = whileLabelStack[top - 1];

    int lb = buf[0];
    
    javafile << "\t\tgoto Lbegin " << lb << endl;
}

void WHILEEnd(){
    int top = whileLabelStack.size() - 1;

    vector<int> buf = whileLabelStack[top];

    int lb = buf[buf.size() - 1];

    javafile << "\tL" << lb << endl;

    whileLabelStack.pop_back();
}