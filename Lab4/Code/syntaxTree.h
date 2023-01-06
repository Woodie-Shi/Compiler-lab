#ifndef _SYNTAXTREE_H
#define _SYNTAXTREE_H

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode_* TreeNode;

#define MAX_CHILDREN 8
enum syntax_type { TYPE_INT, TYPE_OCT, TYPE_HEX, TYPE_FLOAT, TYPE_ID, TYPE_TYPE, OTHER };

struct TreeNode_ {
    char name[32];  // name, e.g. "DefList"
    char val[64];       // value in char* format         
    bool terminal;           // if is terminal node
    union {
        unsigned val_int;
        float val_float;
        char* var_str;
    } data;
    int children_num;
    TreeNode children[MAX_CHILDREN];
    int line;
    enum syntax_type datatype;
};

void tree_display(TreeNode newnode, int depth);                                    
TreeNode node_init(const char* name, enum syntax_type datatype, const char* val);  // terminator node
TreeNode node_insert(const char* name, int line, int node_num, ...);  // node_insert
TreeNode get_child(TreeNode mynode, int child_idx);                   
#endif