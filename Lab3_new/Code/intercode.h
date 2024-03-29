#ifndef __INTERCODE_H__
#define __INTERCODE_H__

#include "syntaxTree.h"
#include "analysis.h"

typedef struct Operand_* Operand;
typedef struct InterCode_* InterCode;
typedef struct InterCodeList_* InterCodeList;
extern int temp_number;   // 临时变量编号
extern int label_number;  // 跳转编号
extern int addr_number;   // 地址编号
struct Operand_ {
    enum {
        OP_VARIABLE,   // 变量
        OP_ADDRESS,    // 数组或结构的地址
        OP_FUNCTION,   // 函数名
        OP_ARRAY,      // 数组变量
        OP_STRUCTURE,  // 结构变量
        OP_LABEL,      // 跳转编号
        OP_TEMP,       // 临时变量
        OP_CONSTANT,   // 常量
    } kind;
    union {
        int var_no;           // 变量编号
        int addr_no;          // 地址编号
        char* func_name;      // 函数名字
        int array_no;         // 数组编号
        int label_no;         // 跳转编号
        int temp_no;          // 临时变量编号
        long long const_val;  // 常量值
    } u;
    Type type;  // 数组元素类型
    int size;   // 数组元素个数
};

struct InterCode_ {
    enum {
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
    } kind;
    union {
        struct {
            Operand op;
        } unary_ir;  // IR_LABEL IR_FUNC IR_GOTO IR_RETURN IR_ARG IR_PARAM IR_READ IR_WRITE
        struct {
            Operand op;
            int size;
        } dec;  // IR_DEC x [size]
        struct {
            Operand right, left;
        } binary_ir;  // IR_ASSIGN IR_ADDR IR_LOAD IR_STORE IR_CALL
        struct {
            Operand res, op1, op2;
        } ternary_ir;  // IR_ADD IR_SUB IR_MUL IR_DIV
        struct {
            Operand x, y, z;
            char relop[64];
        } if_goto;  // IR_IF_GOTO
    } u;
    bool bb_start;       // 基本块的开始
    unsigned int bb_no;  // 所处基本块的编号
};

struct InterCodeList_ {  // 双向链表存储IR
    InterCode code;
    InterCodeList prev, next;
};

InterCodeList init_ir_list();                                 // 初始化IR双向链表头
void add_ir(InterCodeList ir_list_head, InterCode ir);        // 将ir添加到ir_list_head尾部
void delete_ir(InterCodeList ir);                             // 将ir删除
void show_ir_list(InterCodeList ir_list_head, FILE* ir_out);  // 打印IR链表
void show_ir(InterCode ir, FILE* ir_out);                     // 打印IR
void show_op(Operand op, FILE* ir_out);                       // 打印OP
InterCode gen_ir(InterCodeList ir_list_head, int ir_kind, Operand op1, Operand op2, Operand op3, int dec_size,
                 char* relop);                                                 // 生成IR
Operand gen_operand(int operand_kind, long long val, int number, char* name);  // 产生Operand
Operand new_temp();                                                            // 产生一个临时变量
Operand new_addr();                                                            // 产生一个地址
Operand new_label();                                                           // 产生一个跳转标记

void translate_Program(Node root);
void translate_ExtDefList(Node root);
void translate_ExtDef(Node root);
/**
 * 假设4 没有全局变量,无需考虑ExtDecList
 * 变量类型在语义分析部分全部完成,无需考虑Specifier
 */

Operand translate_VarDec(Node root);  // 返回变量OP
void translate_FunDec(Node root);
/**
 * 直接获取函数定义的Field,直接获取参数列表
 * 无需再取考虑VarList ParamDec
 */

void translate_CompSt(Node root);
void translate_StmtList(Node root);
void translate_Stmt(Node root);

void translate_DefList(Node root);
void translate_Def(Node root);
void translate_DecList(Node root);
void translate_Dec(Node root);

void translate_Exp(Node root, Operand place);
void translate_Args(Node root, bool write_func);

void translate_Cond(Node root, Operand true_label, Operand false_label);

Operand array_deep_copy(Operand op_left, Operand op_right);  // 数组深拷贝

Operand load_value(Operand addr);

Operand get_addr(Operand addr, bool is_arg);  // 获取数组的地址，以及该数组是否需要作为实参区分处理

int get_size(Type type);  // 获取数组或者结构体的大小

void dump_translator_node(Node node, char* translator_name);  // debug func

#endif