#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_
#include<stdbool.h>
#include <assert.h>
#include <string.h>
#include "syntaxTree.h"

#define HASHTABLE_SIZE 0x3fff
typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
typedef struct HashNode_* HashNode;
extern HashNode hashtable[HASHTABLE_SIZE + 1];
extern int var_number;

struct Type_ {
    enum { BASIC, ARRAY, STRUCTURE, STRUCTTAG, FUNCTION } kind;
    bool need_free;
    bool is_struct;
    union {
        // 基本类型    0 -> INT, 1 -> FLOAT
        enum { NUM_INT, NUM_FLOAT } basic;

        // 数组类型信息包括元素类型与数组大小构成
        struct {
            Type elem;
            int size;
        } array; 

        // 结构体类型信息是一个链表
        //FieldList structure;
        FieldList structfield;  // point to a struct definition
        FieldList member;     // struct definition

        //函数定义或声明
        struct {
            int argc;  // number of arguments
            FieldList params;
            Type returnVal;
        } function;
    } u;
};

struct FieldList_ {
    char* name;     // 域的名字
    Type type;        // 域的类型
    FieldList tail;   // 下一个域
    bool arg;          // function params
    int id;
};

struct HashNode_ {
    FieldList data;
    HashNode next;
};

void init_hashtable();               // initialize the hashtable
unsigned int hash_pjw(char* name);       // hash_pjw function
void insert_field(FieldList field);  // insert filed to hashtable
FieldList query(char* name);       // look up the item, if find return the index


void Program(TreeNode root);
void ExtDefList(TreeNode root);
void ExtDef(TreeNode root);
void ExtDecList(TreeNode root, Type type);  
Type Specifier(TreeNode root);
Type StructSpecifier(TreeNode root);
char* OptTag(TreeNode root);
char* Tag(TreeNode root);
FieldList VarDec(TreeNode root, Type type, FieldList field);  
void FunDec(TreeNode root, Type type);                  
void VarList(TreeNode root, FieldList field);             
FieldList ParamDec(TreeNode root);
void CompSt(TreeNode root, Type type);    
void Stmtlist(TreeNode root, Type type);  
void Stmt(TreeNode root, Type type);    
void DefList(TreeNode root, FieldList field);             
void Def(TreeNode root, FieldList field);                
void DecList(TreeNode root, Type type, FieldList field);  
void Dec(TreeNode root, Type type, FieldList field);     
Type Exp(TreeNode root);        
FieldList Args(TreeNode root); 

FieldList in_struct(FieldList struct_field, char* member);  
bool check_equivalent(Type a, Type b);                         
bool args_matched(FieldList act_args, FieldList form_args); 
void add_struct_member(TreeNode member, Type mem_type, FieldList struct_field);
void add_func_param(TreeNode param, FieldList func_field);

void show_semantic_error(int err_type, int err_line, char* err_msg, char* err_elm);

#endif