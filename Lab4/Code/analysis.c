#include "analysis.h"

HashNode hashtable[HASHTABLE_SIZE + 1];
int var_number = 0, array_number = 0, func_number = 0;

extern int semantic_errs;
extern int semantic_debug;
void init_hashtable() {
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        hashtable[i] = NULL;
    }
}

unsigned int hash_pjw(char* name) {
    unsigned int val = 0, i;
    for (; *name; name++) {
        val = (val << 2) + *name;
        if (i = val & ~HASHTABLE_SIZE) val = (val ^ (i >> 12)) & HASHTABLE_SIZE;
    }
    assert(val <= HASHTABLE_SIZE);
    return val;
}

void insert_field(FieldList field) {
    unsigned int index = hash_pjw(field->name);
    HashNode node = (HashNode)malloc(sizeof(struct HashNode_));
    switch (field->type->kind) {
        case BASIC:
            field->id = var_number++;
            break;
        case ARRAY:
            field->id = array_number++;
            break;
        case FUNCTION:
            field->id = func_number++;
            break;
        case STRUCTURE:
            break;
        case STRUCTTAG:
            break;
        default:
            assert(0);
            break;
    }
    node->data = field;
    node->next = hashtable[index];
    hashtable[index] = node;
}

FieldList query(char* name) {
    unsigned int index = hash_pjw(name);
    HashNode node = hashtable[index];
    while (node != NULL) {
        if (strcmp(node->data->name, name) == 0) {
            return node->data;
        }
        node = node->next;
    }
    return NULL;
}

void insert_funcfield(char* func_name) {
    Type type = (Type)malloc(sizeof(struct Type_));
    type->kind = BASIC;
    type->u.basic = NUM_INT;
    type->need_free = false;
    FieldList field = (FieldList)malloc(sizeof(struct FieldList_));
    field->tail = NULL;
    field->arg = false;
    field->type = (Type)malloc(sizeof(struct Type_));
    field->type->kind = FUNCTION;
    field->type->need_free = false;
    field->type->u.function.argc = 0;
    field->type->u.function.params = NULL;
    field->type->u.function.returnVal = type;
    field->name = (char*)malloc(strlen(func_name) + 1);
    if (strcmp("write", func_name) == 0) {
        FieldList arg = (FieldList)malloc(sizeof(struct FieldList_));
        arg->name = "";
        arg->arg = false;
        arg->tail = NULL;
        arg->type = type;
        field->type->u.function.argc++;
        field->type->u.function.params = arg;
    }
    strcpy(field->name, func_name);
    insert_field(field);
}

void show_semantic_error(int err_type, int err_line, char* err_msg, char* err_elm) {
    semantic_errs++;
    printf("Error type %d at Line %d: %s", err_type, err_line, err_msg);
    if (err_elm != NULL) {
        printf(" \"%s\"", err_elm);
    }
    printf(".\n");
}

/*Program → ExtDefList*/
void Program(TreeNode root) {
    init_hashtable();
    if (root == NULL) return;
    assert(root->children_num == 1);

    // func read
    insert_funcfield("read");
    // func write
    insert_funcfield("write");

    ExtDefList(get_child(root, 0));
}

// ExtDefList -> ExtDef ExtDefList
void ExtDefList(TreeNode root) {
    if (root == NULL) return;
    assert(root->children_num == 2);
    ExtDef(get_child(root, 0));
    ExtDefList(get_child(root, 1));
}

/* ExtDef → Specifier ExtDecList SEMI
    | Specifier SEMI
    | Specifier FunDec SEMI*/
void ExtDef(TreeNode root) {
    if (root == NULL) return;
    assert(root->children_num == 2 || root->children_num == 3);
    Type type = Specifier(get_child(root, 0));
    if (root->children_num == 3) {
        if (strcmp(get_child(root, 1)->name, "ExtDecList") == 0) {  
            // ExtDef -> Specifier ExtDecList SEMI
            ExtDecList(get_child(root, 1), type);
        } else if (strcmp(get_child(root, 2)->name, "CompSt") == 0) {  
            // ExtDef -> Specifier FunDec CompSt
            FunDec(get_child(root, 1), type);
            CompSt(get_child(root, 2), type);
        }
    } else if (root->children_num == 2) {
        if (strcmp(get_child(root, 1)->name, "SEMI") == 0) {  
            // ExtDef -> Specifier SEMI
        }
    }
}

/* ExtDecList → VarDec
    | VarDec COMMA ExtDecList*/
void ExtDecList(TreeNode root, Type type) {
    if (root == NULL) return;
    assert(root->children_num == 1 || root->children_num == 3);
    if (root->children_num == 1) {  
        // ExtDecList -> VarDec
        VarDec(get_child(root, 0), type, NULL);
    } else if (root->children_num == 3) {  
        // ExtDecList -> VarDec COMMA ExtDecList
        VarDec(get_child(root, 0), type, NULL);
        ExtDecList(get_child(root, 2), type);
    }
}

/*Specifier → TYPE
    | StructSpecifier*/
Type Specifier(TreeNode root) {
    if (root == NULL) return NULL;
    Type type = NULL;
    assert(root->children_num == 1);
    if (strcmp(get_child(root, 0)->name, "TYPE") == 0) {  
        // Specifier -> TYPE
        type = (Type)malloc(sizeof(struct Type_));
        type->kind = BASIC;
        type->need_free = false;
        if (strcmp(get_child(root, 0)->val, "int") == 0) {
            type->u.basic = NUM_INT;
        } else if (strcmp(get_child(root, 0)->val, "float") == 0) {
            type->u.basic = NUM_FLOAT;
        } else {
            assert(0);
        }
    } else if (strcmp(get_child(root, 0)->name, "StructSpecifier") == 0) {  
        // Specifier -> StructSpecifier
        type = StructSpecifier(get_child(root, 0));
    }
    return type;
}

/* StructSpecifier → STRUCT OptTag LC DefList RC
    | STRUCT Tag    */
Type StructSpecifier(TreeNode root) {
    if (root == NULL) return NULL;
    Type type = NULL;
    FieldList field = NULL;
    assert(root->children_num == 2 || root->children_num == 5);
    if (root->children_num == 5) {  
        // StructSpecifier -> STRUCT OptTag LC DefList RC
        char* opt_tag = OptTag(get_child(root, 1));
        if (opt_tag != NULL) {
            if (query(opt_tag) != NULL) {
                show_semantic_error(16, root->lineno, "Duplicated name", opt_tag);
                return NULL;
            }
        }
        field = (FieldList)malloc(sizeof(struct FieldList_));
        field->name = opt_tag;
        field->arg = false;
        field->tail = NULL;
        field->type = (Type)malloc(sizeof(struct Type_));
        field->type->kind = STRUCTTAG;
        field->type->need_free = false;
        field->type->is_struct = false;
        field->type->u.member = NULL;
        if (opt_tag != NULL) insert_field(field);
        DefList(get_child(root, 3), field);
        field->type->is_struct = true;
    } else if (root->children_num == 2) {  
        // StructSpecifier -> STRUCT TAG
        char* tag = Tag(get_child(root, 1));
        field = query(tag);
        if (field == NULL || field->type->is_struct == false) {
            show_semantic_error(17, root->lineno, "Undefined structure", tag);
            return NULL;
        }
    }
    type = (Type)malloc(sizeof(struct Type_));
    type->kind = STRUCTURE;
    type->need_free = false;
    type->u.structfield = field;
    return type;
}

/* OptTag → ID
    | epsilon*/
char* OptTag(TreeNode root) {
    if (root == NULL) return NULL;
    // OptTag -> ID
    assert(root->children_num == 1);
    return get_child(root, 0)->val;
}
/* Tag → ID*/
char* Tag(TreeNode root) {
    if (root == NULL) return NULL;
    assert(root->children_num == 1);
    return get_child(root, 0)->val;
}

/*VarDec → ID
| VarDec LB INT RB*/
FieldList VarDec(TreeNode root, Type type, FieldList field) {
    if (root == NULL) return NULL;
    FieldList var_field = NULL;
    assert(root->children_num == 1 || root->children_num == 4);
    if (root->children_num == 1) {  
        // VarDec -> ID
        char* ID = get_child(root, 0)->val;
        var_field = (FieldList)malloc(sizeof(struct FieldList_));
        var_field->name = ID;
        var_field->type = type;
        var_field->tail = NULL;
        var_field->arg = false;
        if (field != NULL && field->type->kind == STRUCTTAG) {
            if (in_struct(field, ID) != NULL) {
                show_semantic_error(15, root->lineno, "Redefined filed", ID);
                free(var_field);
                var_field = NULL;
            }
        } else if (query(ID) != NULL) {
            show_semantic_error(3, root->lineno, "Redefined variable", ID);
        } else {
            insert_field(var_field);
        }
    } else if (root->children_num == 4) {  
        // VarDec -> VarDec LB INT RB
        Type array_type = (Type)malloc(sizeof(struct Type_));
        array_type->kind = ARRAY;
        array_type->need_free = false;
        array_type->u.array.size = get_child(root, 2)->data.val_int;
        array_type->u.array.elem = type;
        return VarDec(get_child(root, 0), array_type, field);
    }
    return var_field;
}

/*FunDec → ID LP VarList RP
    | ID LP RP*/
void FunDec(TreeNode root, Type type) {
    if (root == NULL) return;
    assert(root->children_num == 3 || root->children_num == 4);
    char* ID = get_child(root, 0)->val;
    FieldList field = NULL;
    FieldList prefield = query(ID);
    if (prefield != NULL && prefield->type->kind == FUNCTION) {  
        // function definition already exist
        show_semantic_error(4, root->lineno, "Redefined function", ID);
    } else {
        field = (FieldList)malloc(sizeof(struct FieldList_));
        field->name = ID;
        field->arg = false;
        field->tail = NULL;
        field->type = (Type)malloc(sizeof(struct Type_));
        field->type->kind = FUNCTION;
        field->type->need_free = false;
        field->type->u.function.argc = 0;
        field->type->u.function.params = NULL;
        field->type->u.function.returnVal = type;
        insert_field(field);
    }
    if (root->children_num == 3) {         
        // FunDec -> ID LP RP
    } else if (root->children_num == 4) {  
        // FunDec -> ID LP VarList RP
        VarList(get_child(root, 2), field);
    }
}

/*VarList → ParamDec COMMA VarList
    | ParamDec*/
void VarList(TreeNode root, FieldList field) {
    if (root == NULL) return;
    assert(root->children_num == 1 || root->children_num == 3);
    if (root->children_num == 1) {  
        // VarList -> ParamDec
        add_func_param(get_child(root, 0), field);
    } else if (root->children_num == 3) {  
        // VarList -> ParamDec COMMA VarList
        add_func_param(get_child(root, 0), field);
        VarList(get_child(root, 2), field);
    }
}

/* ParamDec -> Specifier VarDec*/
FieldList ParamDec(TreeNode root) {
    if (root == NULL) return NULL;
    assert(root->children_num == 2);
    Type type = Specifier(get_child(root, 0));
    return type != NULL ? VarDec(get_child(root, 1), type, NULL) : NULL;
}

/*CompSt → LC DefList StmtList RC
StmtList → Stmt StmtList*/
void CompSt(TreeNode root, Type type) {
    if (root == NULL) return;
    // CompSt -> LC DefList StmtList RC
    assert(root->children_num == 4);
    DefList(get_child(root, 1), NULL);
    Stmtlist(get_child(root, 2), type);
}
void Stmtlist(TreeNode root, Type type) {
    if (root == NULL) return;
    // Stmtlist -> Stmt Stmtlist
    assert(root->children_num == 2);
    Stmt(get_child(root, 0), type);
    Stmtlist(get_child(root, 1), type);
}

/*Stmt → Exp SEMI
| CompSt
| RETURN Exp SEMI
| IF LP Exp RP Stmt
| IF LP Exp RP Stmt ELSE Stmt
| WHILE LP Exp RP Stmt*/
void Stmt(TreeNode root, Type type) {
    if (root == NULL) return;
    assert(root->children_num == 1 || root->children_num == 2 || root->children_num == 3 || root->children_num == 5 ||
           root->children_num == 7);
    if (root->children_num == 1) {  
        // Stmt -> CompSt
        CompSt(get_child(root, 0), type);
    }
    else if (root->children_num == 2) {  
        // Stmt -> Exp SEMI
        Exp(get_child(root, 0));
    }
    else if (root->children_num == 3) {  
        // Stmt -> RETURN Exp SEMI
        Type ret_type = Exp(get_child(root, 1));
        if (ret_type != NULL && check_equivalent(ret_type, type) == 0) {
            show_semantic_error(8, root->lineno, "Type mismatched for return", NULL);
        }
        //dump_type(ret_type, 0);
    }
    else if (root->children_num == 5) {
        /* Stmt -> IF LP Exp RP Stmt
            Stmt -> WHILE LP Exp RP Stmt */
        Type cond_type = Exp(get_child(root, 2));
        if (cond_type != NULL && (cond_type->kind != BASIC || cond_type->u.basic != NUM_INT)) {
            show_semantic_error(7, root->lineno, "Non-int type cannot used as a condition", NULL);
        }
        Stmt(get_child(root, 4), type);
        }
        else if (root->children_num == 7) {  
        // Stmt -> IF LP Exp RP Stmt ELSE Stmt
            Type cond_type = Exp(get_child(root, 2));
            if (cond_type != NULL && (cond_type->kind != BASIC || cond_type->u.basic != NUM_INT)) {
                show_semantic_error(7, root->lineno, "Non-int type cannot used as a condition", NULL);
            }
        Stmt(get_child(root, 4), type);
        Stmt(get_child(root, 6), type);
    }
}

/*DefList → Def DefList
|  epsilon*/
void DefList(TreeNode root, FieldList field) {
    if (root == NULL) return;
    // DefList -> Def DefList
    assert(root->children_num == 2);
    Def(get_child(root, 0), field);
    DefList(get_child(root, 1), field);
}
void Def(TreeNode root, FieldList field) {
    if (root == NULL) return;
    // Def -> Specifier DecList SEMI
    assert(root->children_num == 3);
    Type type = Specifier(get_child(root, 0));
    if (type != NULL) DecList(get_child(root, 1), type, field);
}

/*DecList → Dec | Dec COMMA DecList*/
void DecList(TreeNode root, Type type, FieldList field) {
    if (root == NULL) return;
    assert(root->children_num == 1 || root->children_num == 3);
    if (root->children_num == 1) {  
        // DecList -> Dec
        Dec(get_child(root, 0), type, field);
    } 
    else if (root->children_num == 3) {  
        // DecList -> Dec COMMA DecList
        Dec(get_child(root, 0), type, field);
        DecList(get_child(root, 2), type, field);
    }
}


void Dec(TreeNode root, Type type, FieldList field) {
    if (root == NULL) return;
    assert(root->children_num == 1 || root->children_num == 3);
    if (root->children_num == 1) {  
        // Dec -> VarDec
        if (field != NULL && field->type->kind == STRUCTTAG) {
            add_struct_member(get_child(root, 0), type, field);
        } 
        else {
            VarDec(get_child(root, 0), type, field);
        }
    } 
    else if (root->children_num == 3) {  
        // VarDec ASSIGNOP Exp
        if (field != NULL && field->type->kind == STRUCTTAG) {
            add_struct_member(get_child(root, 0), type, field);
            show_semantic_error(15, root->lineno, "Initialized struct field in definition", NULL);
            return;
        }
        FieldList var_dec = VarDec(get_child(root, 0), type, field);
        Type assign_type = Exp(get_child(root, 2));
        if (var_dec != NULL && check_equivalent(var_dec->type, assign_type) == 0) {
            show_semantic_error(5, root->lineno, "Type mismatched for assignment", NULL);
        }
        if (assign_type != NULL && assign_type->need_free) {
            free(assign_type);
        }
    }
}

/*Expressions
Exp : Exp ASSIGNOP Exp
    | Exp AND Exp
    | Exp OR Exp
    | Exp RELOP Exp
    | Exp PLUS Exp
    | Exp MINUS Exp
    | Exp STAR Exp
    | Exp DIV Exp
    | LP Exp RP
    | MINUS Exp
    | NOT Exp
    | ID LP Args RP
    | ID LP RP
    | Exp LB Exp RB
    | Exp DOT ID
    | ID
    | INT
    | FLOAT*/
Type Exp(TreeNode root) {
    if (root == NULL) return NULL;
    Type type = NULL;
    FieldList result = NULL;
    assert(root->children_num == 1 || root->children_num == 2 || root->children_num == 3 || root->children_num == 4);
    if (root->children_num == 1) {
        if (strcmp(get_child(root, 0)->name, "ID") == 0) { 
            // Exp -> ID
            result = query(get_child(root, 0)->val);
            if (result == NULL || result->type->kind == STRUCTTAG || result->type->kind == FUNCTION) {
                show_semantic_error(1, root->lineno, "Undefined variable", get_child(root, 0)->val);
            } 
            else {
                type = result->type;
            }
        } 
        else {
            type = (Type)malloc(sizeof(struct Type_));
            type->kind = BASIC;
            type->need_free = true;
            if (get_child(root, 0)->datatype == TYPE_INT) {  // Exp -> INT
                type->u.basic = NUM_INT;
            } 
            else if (get_child(root, 0)->datatype == TYPE_FLOAT) {  // Exp -> FLOAT
                type->u.basic = NUM_FLOAT;
            } 
            else {
                assert(0);
            }
        }
    } else if (root->children_num == 2) {
        /*Exp -> NOT Exp
            Exp -> MINUS Exp */
        if (strcmp(get_child(root, 0)->name, "NOT") == 0) {
            type = Exp(get_child(root, 1));
            if (type != NULL && (type->kind != BASIC || type->u.basic != NUM_INT)) {
                show_semantic_error(7, root->lineno, "Non-int type cannot perform logical operations", NULL);
            }
            type = (Type)malloc(sizeof(struct Type_));
            type->kind = BASIC;
            type->u.basic = NUM_INT;
            type->need_free = true;
        } 
        else if (strcmp(get_child(root, 0)->name, "MINUS") == 0) {
            type = Exp(get_child(root, 1));
        }
    } 
    else if (root->children_num == 3) {
        if (strcmp(get_child(root, 0)->name, "LP") == 0) {  // Exp -> LP Exp RP
            type = Exp(get_child(root, 1));
        } 
        else if (strcmp(get_child(root, 0)->name, "ID") == 0) {  // Exp -> ID LP RP
            result = query(get_child(root, 0)->val);
            if (result == NULL) {
                show_semantic_error(2, root->lineno, "Undefined function", get_child(root, 0)->val);
            } 
            else if (result->type->kind != FUNCTION) {
                show_semantic_error(11, root->lineno, "Not a function", get_child(root, 0)->val);
            } 
            else if (args_matched(NULL, result->type->u.function.params) == 0) {
                show_semantic_error(9, root->lineno, "Function is not applicable for arguments", get_child(root, 0)->val);
            }
            if (result != NULL && result->type->kind == FUNCTION) {
                type = result->type->u.function.returnVal;
            }
        } 
        else if (strcmp(get_child(root, 1)->name, "DOT") == 0) {  // Exp -> Exp DOT ID
            Type type1 = Exp(get_child(root, 0));
            if (type1 == NULL) {
            } 
            else if (type1->kind != STRUCTURE) {
                show_semantic_error(13, root->lineno, "Illegal use of", ".");
            } 
            else {
                char* mem_name = get_child(root, 2)->val;
                FieldList member_point = in_struct(type1->u.structfield, mem_name);
                if (member_point == NULL) {
                    show_semantic_error(14, root->lineno, "Non-existent field", mem_name);
                } 
                else {
                    type = member_point->type;
                }
            }
        } 
        else if (strcmp(get_child(root, 1)->name, "ASSIGNOP") == 0) {  // Exp ASSIGNOP Exp
            TreeNode node_left = get_child(root, 0);
            type = Exp(node_left);
            Type type_right = Exp(get_child(root, 2));
            if (type == NULL) {
            } 
            else if (!((node_left->children_num == 1 && strcmp(get_child(node_left, 0)->name, "ID") == 0) ||
                         (node_left->children_num == 3 && strcmp(get_child(node_left, 1)->name, "DOT") == 0) ||
                         (node_left->children_num == 4 && strcmp(get_child(node_left, 0)->name, "Exp") == 0))) {
                show_semantic_error(6, root->lineno, "The left-hand side of an assignment must be a variable", NULL);
            }
            if (check_equivalent(type, type_right) == 0) {
                show_semantic_error(5, root->lineno, "Type mismatched for assignment", NULL);
            }
        } 
        else {
            /*Exp -> Exp AND Exp
                Exp -> Exp OR Exp
                Exp -> Exp RELOP Exp
                Exp -> Exp PLUS Exp
                Exp -> Exp MINUS Exp
                Exp -> Exp STAR Exp
                Exp -> Exp DIV Exp  */
            type = Exp(get_child(root, 0));
            Type type_right = Exp(get_child(root, 2));

            if (check_equivalent(type, type_right) == 0) {
                show_semantic_error(7, root->lineno, "Type mismatched for operands", NULL);
            } 
            else if (strcmp(get_child(root, 1)->name, "AND") == 0 || strcmp(get_child(root, 1)->name, "OR") == 0) {
                if (type != NULL && (type->kind != BASIC || type->u.basic != NUM_INT)) {
                    show_semantic_error(7, root->lineno, "Non-int type cannot perform logical operations", NULL);
                }
                type = (Type)malloc(sizeof(struct Type_));
                type->kind = BASIC;
                type->u.basic = NUM_INT;
                type->need_free = true;
            } 
            else if (strcmp(get_child(root, 1)->name, "RELOP") == 0) {
                type = (Type)malloc(sizeof(struct Type_));
                type->kind = BASIC;
                type->u.basic = NUM_INT;
                type->need_free = true;
            }
        }
    } 
    else if (root->children_num == 4) {
        if (strcmp(get_child(root, 0)->name, "ID") == 0) {  
            // Exp -> ID LP Args RP
            result = query(get_child(root, 0)->val);
            if (result == NULL) {
                show_semantic_error(2, root->lineno, "Undefined function", get_child(root, 0)->val);
            } 
            else if (result->type->kind != FUNCTION) {
                show_semantic_error(11, root->lineno, "Not a function", get_child(root, 0)->val);
            } 
            else {
                if (args_matched(Args(get_child(root, 2)), result->type->u.function.params) == 0) {
                    show_semantic_error(9, root->lineno, "Function is not applicable for arguments", get_child(root, 0)->val);
                }
            }
            if (result != NULL && result->type->kind == FUNCTION) {
                type = result->type->u.function.returnVal;
            }
        } else if (strcmp(get_child(root, 0)->name, "Exp") == 0) {  
            // Exp -> Exp LB Exp RB
            Type type1 = Exp(get_child(root, 0));
            if (type1 == NULL) {
            } 
            else if (type1->kind != ARRAY) {
                show_semantic_error(10, root->lineno, "Not an array", NULL);
            } 
            else {
                type = type1->u.array.elem;
            }
            Type type2 = Exp(get_child(root, 2));
            if (type2 != NULL && (type2->kind != BASIC || type2->u.basic != NUM_INT)) {
                show_semantic_error(12, root->lineno, "Not an integer", NULL);
            }
        }
    }
    return type;
}

FieldList Args(TreeNode root) {
    if (root == NULL) return NULL;
    assert(root->children_num == 1 || root->children_num == 3);
    Type args_type = Exp(get_child(root, 0));
    if (args_type == NULL) return NULL;
    FieldList args = (FieldList)malloc(sizeof(struct FieldList_));
    args->name = "arg";
    args->type = args_type;
    args->tail = NULL;
    args->arg = false;
    if (root->children_num == 1) {         
    // Args -> Exp
    } 
    else if (root->children_num == 3) {  
        // Args -> Exp COMMA Args
        args->tail = Args(get_child(root, 2));
    }
    return args;
}

FieldList in_struct(FieldList struct_field, char* member) {
    if (struct_field == NULL || struct_field->type->kind != STRUCTTAG) return NULL;
    FieldList member_point = struct_field->type->u.member;
    while (member_point != NULL) {
        if (strcmp(member_point->name, member) == 0) {
            return member_point;
        }
        member_point = member_point->tail;
    }
    return NULL;
}

bool check_equivalent(Type a, Type b) {
    if (a == NULL || b == NULL) return false;
    if (a == b) return true;
    if (a->kind != b->kind) return false;
    FieldList a_member = a->u.member;
    FieldList b_member = b->u.member;
    switch (a->kind) {
        case BASIC:
            return a->u.basic == b->u.basic;
            break;
        case ARRAY:
            return check_equivalent(a->u.array.elem, b->u.array.elem);
            break;
        case STRUCTURE:
            return check_equivalent(a->u.structfield->type, b->u.structfield->type);
            break;
        case STRUCTTAG:
            while (a_member != NULL || b_member != NULL) {
                if (a_member == NULL || b_member == NULL) return false;
                if (check_equivalent(a_member->type, b_member->type) == 0) return false;
                a_member = a_member->tail;
                b_member = b_member->tail;
            }
            break;
        case FUNCTION:
            assert(0);
            break;
    }
    return true;
}

bool args_matched(FieldList act_args, FieldList form_args) {
    if (act_args == NULL && form_args == NULL) return true;
    if (act_args == NULL || form_args == NULL) return false;
    while (act_args != NULL || form_args != NULL) {
        if (act_args == NULL || form_args == NULL) return false;
        if (check_equivalent(act_args->type, form_args->type) == 0) return false;
        act_args = act_args->tail;
        form_args = form_args->tail;
    }
    return true;
}

void add_struct_member(TreeNode member, Type mem_type, FieldList struct_field) {
    assert(struct_field != NULL);
    FieldList mem_field = VarDec(member, mem_type, struct_field);
    FieldList temp_field = struct_field->type->u.member;
    if (mem_field == NULL) return;
    mem_field->arg = false;
    if (struct_field->type->u.member == NULL) {
        struct_field->type->u.member = mem_field;
    } else {
        while (temp_field->tail != NULL) temp_field = temp_field->tail;
        temp_field->tail = mem_field;
    }
}

void add_func_param(TreeNode param, FieldList func_field) {
    FieldList arg_field = ParamDec(param);
    if (func_field == NULL || arg_field == NULL) return;
    func_field->type->u.function.argc++;
    arg_field->arg = true;
    FieldList temp_field = func_field->type->u.function.params;
    if (func_field->type->u.function.params == NULL) {
        func_field->type->u.function.params = arg_field;
    } 
    else {
        while (temp_field->tail != NULL) temp_field = temp_field->tail;
        temp_field->tail = arg_field;
    }
}