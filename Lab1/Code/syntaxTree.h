#ifndef _SYNTAXTREE_H
#define _SYNTAXTREE_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern char *yytext;
extern int yyleng;
extern int yylineno;

enum syntax_type {lexical, syntactic};
typedef struct TreeNode{
    char* name;
    union{
        int val_int;
        float val_float;
        char* val_str;
    };
    int children_num;
    struct TreeNode** children;
    int lineno;
    enum syntax_type type;
}TreeNode;

TreeNode* node_init(char* _name, enum syntax_type _type);
void node_insert(int num, TreeNode*parent,  TreeNode*_children[]);
void tree_display(TreeNode* root, int depth);

#endif