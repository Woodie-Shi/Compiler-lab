#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_
#include<stdbool.h>
#include <assert.h>
#include "syntaxTree.h"

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
#define HASH 0x3fff
#define FUNCTION 0x3ff

struct Type_
{
    enum { BASIC, ARRAY, STRUCTURE } kind;
    union
    {
        // 基本类型    1 -> INT, 2 -> FLOAT
        int basic;

        // 数组类型信息包括元素类型与数组大小构成
        struct {
            Type elem; 
            int size; 
        } array;

        // 结构体类型信息是一个链表
        //FieldList structure;
        //增加一个名
        struct {
            char* id;
            FieldList structfield;
        }structure;

        //函数定义或声明
        struct{
            enum {DECLARED, DEFINED} status;
            Type returnVal;
            FieldList params;
        }function;
        
    } u;
};

struct FieldList_
{
    char* name; // 域的名字
    Type type; // 域的类型
    FieldList tail; // 下一个域
    int lineno;
};

extern FieldList hash_table[HASH];
extern char* func_table[FUNCTION];

unsigned int hash_pjw(char* name);

void init_hash();
bool fill_in(FieldList f);
FieldList query(char* name);

void Program(TreeNode* root);
void ExtDefList(TreeNode* root);
Type Specifier(TreeNode* root);
FieldList DefList(TreeNode* root);
FieldList VarDec(TreeNode* root, Type type);
Type FunDec(TreeNode* root, Type return_type, bool flag);
void CompSt(TreeNode* root, Type function);
void Stmt(TreeNode* root, Type function);
Type Exp(TreeNode* root);

#endif