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
extern int var_number;  // 变量编号，便于优化处理

struct Type_ {
    enum { BASIC, ARRAY, STRUCTURE, STRUCTTAG, FUNCTION } kind;
    bool need_free;
    bool struct_def_done;
    union {
        enum { NUM_INT, NUM_FLOAT } basic;  // 基本类型
        struct {
            Type elem;
            int size;
        } array;              // 数组类型信息包括元素类型与数组大小构成
        FieldList structure;  // point to a struct definition
        FieldList member;     // struct definition
        struct {
            int argc;  // number of arguments
            FieldList argv;
            Type ret;  // return type
        } function;
    } u;
};

struct FieldList_ {
    char* name;      // 域的名字
    Type type;       // 域的类型
    FieldList tail;  // 下一个域
    bool arg;        // 函数形参
    int id;          // 变量id
};

struct HashNode_ {
    FieldList data;
    HashNode link;
};
void init_hashtable();               // initialize the hashtable
unsigned int hash(char* name);       // hash function
void insert_field(FieldList field);  // insert filed to hashtable
FieldList query(char* name);       // look up the item, if find return the index



void add_READ_WRITE_func();  // add read write function to hashtable

void Program(Node root);
void ExtDefList(Node root);
void ExtDef(Node root);
void ExtDecList(Node root, Type type);  // type: ExtDef's Specifier type

Type Specifier(Node root);
Type StructSpecifier(Node root);
char* OptTag(Node root);
char* Tag(Node root);

FieldList VarDec(Node root, Type type, FieldList field);  // type: VarDec type field: StructTag pointer
void FunDec(Node root, Type type);                        // type: FunDec return type
void VarList(Node root, FieldList field);                 // filed: FunDec argc argv
FieldList ParamDec(Node root);

void CompSt(Node root, Type type);    // type: FunDec return type
void Stmtlist(Node root, Type type);  // type: FunDec return type
void Stmt(Node root, Type type);      // type: FunDec return type

void DefList(Node root, FieldList field);             // field: StructTag pointer
void Def(Node root, FieldList field);                 // field: StructTag pointer
void DecList(Node root, Type type, FieldList field);  // type: VarDec type field: StructTag pointer
void Dec(Node root, Type type, FieldList field);      // type: VarDec type field: StructTag pointer

Type Exp(Node root);        // return exp type
FieldList Args(Node root);  // return arguments

FieldList have_member(FieldList struct_field, char* member);  // check member in filed
bool type_matched(Type a, Type b);                            // check type matched, 1: matched, 0: not matched
bool args_matched(FieldList act_args,
                  FieldList form_args);  // check function arguments matched
void add_struct_member(Node member, Type mem_type, FieldList struct_field);
void add_func_parameter(Node param, FieldList func_field);
void dump_field(FieldList field, int depth);
void dump_type(Type type, int depth);
void dump_node(Node node);
void dump_semantic_error(int err_type, int err_line, char* err_msg, char* err_elm);

#endif