#include "syntaxTree.h"
void tree_display(TreeNode newnode, int depth) {
    if (newnode == NULL) return;
    for (int i = 0; i < depth; i++) printf("  ");
    printf("%s", newnode->name);
    if (newnode->terminal) {
        switch (newnode->datatype) {
            case TYPE_ID:
                printf(": %s", newnode->data.var_str);
                break;
            case TYPE_TYPE:
                printf(": %s", newnode->data.var_str);
                break;
            case TYPE_FLOAT:
                printf(": %.6f", newnode->data.val_float);
                break;
            case TYPE_INT:
                printf(": %u", newnode->data.val_int);
                break;
            default:
                break;
        }
    } else {
        printf(" (%d)", newnode->lineno);
    }
    printf("\n");
    if (newnode->terminal == 0) {
        for (int i = 0; i < newnode->children_num; i++) {
            tree_display(newnode->children[i], depth + 1);
        }
    }
}
TreeNode node_init(const char* name, enum syntax_type datatype, const char* val) {
    TreeNode newnode = (TreeNode)malloc(sizeof(struct TreeNode_));
    newnode->terminal = 1;
    newnode->datatype = datatype;
    sscanf(name, "%s", newnode->name);
    if (val) sscanf(val, "%s", newnode->val);
    switch (newnode->datatype) {
        case TYPE_ID:
            sscanf(val, "%s", newnode->data.var_str);
            break;
        case TYPE_TYPE:
            sscanf(val, "%s", newnode->data.var_str);
            break;
        case TYPE_FLOAT:
            sscanf(val, "%f", &newnode->data.val_float);
            break;
        case TYPE_INT:
            sscanf(val, "%u", &newnode->data.val_int);
            break;
        case TYPE_OCT:
            sscanf(val, "%o", &newnode->data.val_int);
            newnode->datatype = TYPE_INT;
            break;
        case TYPE_HEX:
            sscanf(val, "%x", &newnode->data.val_int);
            newnode->datatype = TYPE_INT;
            break;
        default:
            break;
    }
    return newnode;
}
TreeNode node_insert(const char* name, int lineno, int node_num, ...) {
    TreeNode newnode = (TreeNode)malloc(sizeof(struct TreeNode_));
    for (int i = 0; i < MAX_CHILDREN; i++) {
        newnode->children[i] = NULL;
    }
    newnode->lineno = lineno;
    newnode->terminal = 0;
    newnode->children_num = node_num;
    sscanf(name, "%s", newnode->name);
    va_list valist;
    va_start(valist, node_num);
    for (int i = 0; i < node_num; i++) {
        newnode->children[i] = va_arg(valist, TreeNode);
    }
    va_end(valist);
    return newnode;
}
TreeNode get_child(TreeNode newnode, int child_idx) {
    assert(child_idx < newnode->children_num);
    return newnode->children[child_idx];
}