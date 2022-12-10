#include "syntaxTree.h"
TreeNode* node_init(char* _name, enum syntax_type _type){
    struct TreeNode* newnode = (struct TreeNode* )malloc(sizeof(struct TreeNode));
    newnode->children_num = 0;
    newnode->children = NULL;
    newnode->name = _name;
    newnode->type = _type;
    newnode->lineno = yylineno;
    return newnode;
}
void node_insert(int num, TreeNode* parent, TreeNode* _children[]) {
    parent->children_num = num;
    parent->children = (TreeNode**)malloc(num * sizeof(TreeNode*));
    for (int i = 0; i < num; i++) {
        parent->children[i] = _children[i];
        if (_children[i]->lineno < parent->lineno) parent->lineno = _children[i]->lineno;
    }
}
void tree_display(TreeNode* root, int depth) {
    if (root->type == syntactic && !root->children_num) return;
    for (int i = 0; i < depth; i++) printf("  ");
    printf("%s", root->name);
    if (root->type == syntactic) printf(" (%d)\n", root->lineno);
    else if (!strcmp(root->name, "INT")) printf(": %d\n", root->val_int);
    else if (!strcmp(root->name, "FLOAT")) printf(": %f\n", root->val_float);
    else if (!strcmp(root->name, "ID") || !strcmp(root->name, "TYPE")) printf(": %s\n", root->val_str);
    else printf("\n");
    for (int i = 0; i < root->children_num; i++) {
        tree_display(root->children[i], depth + 1);
    }
}
