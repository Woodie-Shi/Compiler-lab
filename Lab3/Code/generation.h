#ifndef _GENERATION_H
#define _GENERATION_H
#include "analysis.h"
typedef struct Operand_* Operand;
typedef struct InterCode_*  InterCode;
typedef struct InterCodes_* InterCodes;
typedef struct Arg_* Arg;

enum OPERAND_KIND {VARIABLE, CONSTANT, FUNC};
enum INTER_CODE_KIND {
    LABEL_, FUNC_, 
    ASSIGN_, ADD_, SUB_, MUL_, DIV_, 
	GOTO_, IF_GOTO_, 
    RETURN_, DEC_, ARG_,  CALL_, PARAM_, 
    READ_, WRITE_
};

enum TYPE {ADDRESS, STAR, NORMAL};

struct Operand_ {
    enum OPERAND_KIND kind;
    enum TYPE type;
    union {
        int value;
        char* str;
    } u;
};

struct InterCode_ {
    enum INTER_CODE_KIND kind; 
    union {
        //struct { Operand right, left; } assign;
        struct {Operand op; } singleop;
        //struct { Operand result, op1, op2; } binop;
		struct {Operand dest, src;} binop;	
		struct {Operand op1, op2, dest; }tripleop;

		struct {Operand op1, op2, dest; char *relop;} if_goto;
        struct {Operand var; int size; } dec;
    } u;
};

// 传实参
struct Arg_ {
	Operand arg;
	Arg next;
};

// 函数参数声明
struct Param {
	char *var;
	struct Param *next;
};

struct InterCodes_ { 
    InterCode code; 
    InterCodes prev, next; 
};

void translate(TreeNode* root, FILE *output);
void translate_ExtDefList(struct TreeNode *root);
void translate_DefList(struct TreeNode *root);
void translate_CompSt(struct TreeNode *root);
void translate_Stmt(struct TreeNode *root);
void translate_Cond(struct TreeNode *root, Operand lable_true, Operand lable_false);
void translate_Func(struct TreeNode *root, Operand place);
void translate_Exp(struct TreeNode *root, Operand place);
#endif