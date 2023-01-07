#ifndef __OBJCODE_H__
#define __OBJCODE_H__
#include "intercode.h"

#define REGISTER_NUM 32
typedef struct Register_ Register;
typedef struct Variable_* Variable;
typedef struct VariableList_* VariableList;

struct Register_ {
    char* name;
    enum { FREE, BUSY } status;
    Variable var;     
};

struct Variable_ {
    int reg_no;
    int offset;
    Operand op;
};

struct VariableList_ {
    Variable var;
    VariableList next;
};

void generate(InterCodeList ir_list, FILE* code_out);

#endif