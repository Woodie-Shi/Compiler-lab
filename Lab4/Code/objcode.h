#ifndef _OBJCODE_H
#define _OBJCODE_H
#include "intercode.h"
#include "optimization.h"

#define REGISTER_NUM 32
typedef struct Register_ Register;
typedef struct Variable_* Variable;
typedef struct VariableList_* VariableList;

extern int local_offset;            // 函数内部变量偏移量
extern int arg_num;                 // 函数调用传递的参数
extern int param_num;               // 函数形式参数
extern VariableList local_varlist;  // 函数内部变量链表

struct Register_ {
    char* name;
    enum { FREE, BUSY } status;
    Variable var;     
};

extern struct Register_ regs[REGISTER_NUM];

struct Variable_ {
    int reg_no;
    int offset;
    Operand op;
};

struct VariableList_ {
    Variable var;
    VariableList next;
};

//void generate(InterCodeList ir_list, FILE* code_out);
void gencode(FILE* code_out);
void init_registers();
void init_environment(FILE* code_out);
void init_varlist();

void initsymbol_fb(FunctionBlock fb, FILE* code_out);
void gencode_fb(FunctionBlock fb, FILE* code_out);
void release_varlist();

void initsymbol_bb(BasicBlock bb, FILE* code_out);
void initsymbol_ir(InterCode ir, FILE* code_out);
void gencode_bb(BasicBlock bb, FILE* code_out);
void gencode_ir(InterCode ir, FILE* code_out);
void gen_ir_LABEL(InterCode ir, FILE* code_out);
void gen_ir_FUNC(InterCode ir, FILE* code_out);
void gen_ir_GOTO(InterCode ir, FILE* code_out);
void gen_ir_RETURN(InterCode ir, FILE* code_out);
void gen_ir_ARG(InterCode ir, FILE* code_out);
void gen_ir_PARAM(InterCode ir, FILE* code_out);
void gen_ir_READ(InterCode ir, FILE* code_out);
void gen_ir_WRITE(InterCode ir, FILE* code_out);
void gen_ir_DEC(InterCode ir, FILE* code_out);
void gen_ir_ASSIGN_ADDR(InterCode ir, FILE* code_out);
void gen_ir_LOAD_STORE(InterCode ir, FILE* code_out);
void gen_ir_CALL(InterCode ir, FILE* code_out);
void gen_ir_ARITH(InterCode ir, FILE* code_out);  // 算术运算
void gen_ir_IF_GOTO(InterCode ir, FILE* code_out);

void insert_var(Variable var);

Variable find_var(Operand op);                       // 查找变量是否在当前变量链表中
void insert_op(Operand op);                          // 将op对应的变量加入符号表中
int get_reg(Operand op, bool left, FILE* code_out);  // 为操作数选择寄存器
void store_reg(int reg_no, FILE* code_out);          // 将寄存器保存变量存回内存
void clear_reg(int reg_no);                          // 将寄存器置为空闲

#endif