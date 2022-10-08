#include<stdio.h>
#include<string.h>

extern char *yytext;
extern int yyleng;
extern int yylineno;

enum syntax_type {lexical, syntactic};
struct TreeNode{
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
};

struct TreeNode* node_init(char* _name, enum syntax_type _type);
void node_insert(int num, struct TreeNode*parent, struct TreeNode*_children);
void tree_display(struct TreeNode* root, int depth);