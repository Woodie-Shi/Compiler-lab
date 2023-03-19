#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_
#include<stdbool.h>
#include <assert.h>
#include <string.h>
#include "syntaxTree.h"

#define TABLESIZE 0x3fff

typedef struct HashTableNode_ *HashTableNode;
typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
typedef struct SymbolTableNode_* SymbolTableNode;
typedef struct FunctionTable_* FunctionTable;

typedef struct Type_
{
    enum
    {
        BASIC,
        ARRAY,
        STRUCTURE,
        FUNCTION
    } kind;
    union
    {
        int basic; //基本类型:0为int, 1为float
        struct
        {
            int size;     //数组大小
            Type element; //元素类型
        } array;
        struct
        { //数组类型信息
            char *name;
            FieldList structures;
        } structure; //结构体类型信息
        struct
        {
            int parameterNum; //参数个数
            FieldList parameters;
            Type returnType; //返回值类型
        } function;          //函数类型信息
    } u;
} Type_;

/* FieldList_ 域信息 */
typedef struct FieldList_
{
    char *name;              //域的名字
    Type type;               //域的类型
    FieldList nextFieldList; //下一个域
} FieldList_;

/* SymbolTableNode_ 符号表节点 */
typedef struct SymbolTableNode_
{
    Type type;
    char *name;
    int kind;       // 0 var 1 struct 2 function
    bool isDefined; //是否定义
    int depth;
    int var_no;
    int isAddress;
    int offset;
    char *structName;
    SymbolTableNode sameHashSymbolTableNode;
    SymbolTableNode controlScopeSymbolTableNode;
} SymbolTableNode_;

/* HashTable 符号表 */
typedef struct HashTableNode_
{
    SymbolTableNode symbolTableNode;
    HashTableNode nextHashTableNode;
} HashTableNode_;

/* FunctionTable 函数表 */
struct FunctionTable_
{
    char *name;
    int functionLineNumber;
    FunctionTable next;
};

/* SemanticError 错误类型 */
typedef enum SemanticError
{
    Undefined_Variable,
    Undefined_Function,
    Redefined_Variable_Name,
    Redefined_Function,
    AssignOP_Type_Dismatch,
    Leftside_Rvalue_Error,
    Operand_Type_Dismatch,
    Return_Type_Dismatch,
    Func_Call_Parameter_Dismatch,
    Operate_Others_As_Array,
    Operate_Basic_As_Func,
    Array_Float_Index,
    Operate_Others_As_Struct,
    Undefined_Field,
    Redefined_Field,
    Redefined_Field_Name,
    Undefined_Struct,
    Undefined_Function_But_Declaration,
    Conflict_Decordef_Funcion
} SemanticError;

unsigned int hash_pjw(char *name);
/* initHashTable 初始化符号表 */
HashTableNode initHashTable();
/* initSymbolTableNode 初始化符号表节点 */
SymbolTableNode initSymbolTableNode(Type type, char *name, int isDefined, int depth);
/* getSymbolTableNode 查找符号表节点 */
SymbolTableNode getSymbolTableNode(char *name, int depth);
/* insertHashTable 节点插入符号表 */
void insertHashTable(SymbolTableNode symbolTableNode, HashTableNode hashTableNode);
/* enterInnermostHashTable 进入哈希表最内层 */
HashTableNode enterInnermostHashTable();
/* deleteLocalVariable 删除局部变量 */
void deleteLocalVariable();
/* 删除节点 */
void deleteNode(char *name, int depth, HashTableNode hashTableNode);
/* createNewSymbolTableNode 创建新符号表节点 */
SymbolTableNode createNewSymbolTableNode(Type type, char *name, int kind, bool isDefined, int depth);
/* insertFunction 插入函数节点 */
void insertFunction(char *name, int functionLineNumber);
/* insertStruct 插入结构体节点 */
int insertStruct(Type type, char *name, int offset, char *structName);
/* getLocalVariable 寻找局部变量 */
bool getLocalVariable(Type *type, char *name, int *isDefined, int depth, int mkd);
/* getGlobalVariable 寻找全局变量 */
bool getGlobalVariable(Type *type, char *name, int *isDefined, int depth, int *kind);
/* getStruct 查找结构体节点 */
SymbolTableNode getStruct(char *name);
/* isExistStruct查找结构体 */
bool isExistStruct(Type *type, char *name);
/* printSemanticError 打印语义错误 */
void printSemanticError(enum SemanticError errortype, int line, char *message);
/* typeEqual 检查两个类型是否相等 */
bool typeEqual(Type t1, Type t2);
/* arrayStrongEqual 检查两个数组是否强相等 */
bool arrayStrongEqual(Type t1, Type t2);

/* 创建read函数 */
void createRead();
/* 创建write函数 */
void createWrite();

/* Program 语义分析起点 */
void Program(TreeNode root);
/* ExtDefList ExtDefList检查 */
void ExtDefList(TreeNode root);
/* ExtDef ExtDef检查 */
void ExtDef(TreeNode root);
/* ExtDecList ExtDecList检查 */
void ExtDecList(TreeNode root, Type type);
/* Specifier Specifier检查 */
Type Specifier(TreeNode root);
/* VarDec VarDec检查 */
FieldList VarDec(TreeNode root, Type type);
/* FunDec FunDec检查 */
int FunDec(TreeNode root, bool isDefined, HashTableNode hashTableNode, Type type);
/* VarList VarList检查 */
FieldList VarList(TreeNode root, HashTableNode hashTableNode);
/* ParamDec ParamDec检查 */
FieldList ParamDec(TreeNode root);
/* CompSt CompSt检查 */
void CompSt(TreeNode root, HashTableNode hashTableNode, Type type);
/* StmtList StmtList检查 */
void StmtList(TreeNode root, HashTableNode hashTableNode, Type type);
/* Stmt Stmt检查 */
void Stmt(TreeNode root, HashTableNode hashTableNode, Type type);
/* DefList DefList检查 */
void DefList(TreeNode root, HashTableNode hashTableNode);
/* Def Def检查 */
void Def(TreeNode root, HashTableNode hashTableNode);
/* DecList Defcist检查 */
void DecList(TreeNode root, HashTableNode hashTableNode, Type type);
/* Dec Dec检查 */
void Dec(TreeNode root, HashTableNode hashTableNode, Type type);
/* Exp Exp检查 */
Type Exp(TreeNode root);
/* Args Args检查 */
int Args(TreeNode root, FieldList parameters);
/* StructDef StructDef检查 */
FieldList StructDef(TreeNode root, char *name, int curOffset, int *tmpOffset);
/* StructDec StructDef检查 */
FieldList StructDec(TreeNode root, Type type);

#endif