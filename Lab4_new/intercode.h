#ifndef _INTERCODE_H
#define _INTERCODE_H

#include "syntaxTree.h"
#include "analysis.h"

typedef struct Operand_* Operand;
typedef struct InterCode_* InterCode;
typedef struct InterCodeList_* InterCodeList;

extern int temp_number;   // temp val
extern int label_number;  // label
extern int addr_number;   // address

enum OPERAND_KIND {
    OP_VARIABLE,          // var
    OP_ADDRESS,          // address of array or struct
    OP_ARRAY,                // array
    OP_STRUCTURE,   // struct
    OP_FUNCTION,      // func
    OP_LABEL,               // label
    OP_TEMP,                 // temp val
    OP_CONSTANT,     // constant val
};

enum INTER_CODE_KIND {
    IR_LABEL,    // LABEL x :
    IR_FUNC,     // FUNCTION f :
    IR_GOTO,     // GOTO x
    IR_RETURN,   // RETURN x
    IR_ARG,      // ARG x
    IR_PARAM,    // PARAM x
    IR_READ,     // READ x
    IR_WRITE,    // WRITE x
    IR_DEC,      // DEC x [size]
    IR_ASSIGN,   // x := y
    IR_ADDR,     // x := &y
    IR_LOAD,     // x := *y
    IR_STORE,    // *x := y
    IR_CALL,     // x := CALL f
    IR_ADD,      // x := y+z
    IR_SUB,      // x := y-z
    IR_MUL,      // x := y*z
    IR_DIV,      // x := y/z
    IR_IF_GOTO,  // IF x [relop] y GOTO z
};

struct Operand_ {
    enum OPERAND_KIND kind;
    union {
        int var_no;           // 变量编号
        int temp_no;          // 临时变量编号
        int label_no;         // 跳转编号
        int addr_no;          // 地址编号

        long long const_val;  // 常量值
        int array_no;         // 数组编号
        char* func_name;      // 函数名字
    } u;

    Type type;  // type of array
    int size;       // size of array 
};

struct InterCode_ {
    enum INTER_CODE_KIND kind;
    union {
        struct { Operand op; } singleop; 
        struct { Operand right, left; } binop; 
        struct { Operand res, op1, op2; } tripleop;
        struct { Operand x, y, z; char relop[64]; } if_goto;
        struct { Operand op; int size; } dec; 
    } u;
};

struct InterCodeList_ {
    InterCode code;
    InterCodeList prev, next;
};

void translate_Program(TreeNode root);
void translate_ExtDefList(TreeNode root);
void translate_ExtDef(TreeNode root);
Operand translate_VarDec(TreeNode root);
void translate_FunDec(TreeNode root);
void translate_CompSt(TreeNode root);
void translate_StmtList(TreeNode root);
void translate_Stmt(TreeNode root);
void translate_DefList(TreeNode root);
void translate_Def(TreeNode root);
void translate_DecList(TreeNode root);
void translate_Dec(TreeNode root);
void translate_Exp(TreeNode root, Operand place);
void translate_Args(TreeNode root, bool write_func);
void translate_Cond(TreeNode root, Operand true_label, Operand false_label);

void show_ir_list(InterCodeList ir_list_head, FILE* ir_out);

#endif