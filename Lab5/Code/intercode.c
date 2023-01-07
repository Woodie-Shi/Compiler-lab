#include "intercode.h"
#include <string.h>

int temp_number = 0; 
int label_number = 0; 
int addr_number = 0;
extern InterCodeList* label_array;
extern InterCodeList IrList;

InterCodeList init_ir_list() {
    InterCodeList ir_list_head = (InterCodeList)malloc(sizeof(struct InterCodeList_));
    assert(ir_list_head != NULL);
    ir_list_head->code = NULL;
    ir_list_head->prev = ir_list_head->next = ir_list_head;
    return ir_list_head;
}

void add_ir(InterCodeList ir_list_head, InterCode ir) {
    if (ir == NULL) return;
    InterCodeList new_term = (InterCodeList)malloc(sizeof(struct InterCodeList_));
    assert(new_term != NULL);
    new_term->code = ir;
    InterCodeList tail = ir_list_head->prev;
    tail->next = new_term;
    new_term->prev = tail;
    ir_list_head->prev = new_term;
    new_term->next = ir_list_head;
}

void delete_ir(InterCodeList ir) {
    if (ir == NULL) return;
    InterCodeList prev = ir->prev;
    InterCodeList next = ir->next;
    assert(prev != next && ir != next && ir != prev);
    prev->next = next;
    next->prev = prev;
}

void show_op(Operand op, FILE* ir_out) {
    if (op == NULL) return;
    switch (op->kind) {
        case OP_VARIABLE:
            fprintf(ir_out, "v%d ", op->u.var_no);
            break;
        case OP_ADDRESS:
            fprintf(ir_out, "addr%d ", op->u.addr_no);
            break;
        case OP_FUNCTION:
            fprintf(ir_out, "%s ", op->u.func_name);
            break;
        case OP_ARRAY:
            fprintf(ir_out, "array%d ", op->u.array_no);
            break;
        case OP_STRUCTURE:
            break;
        case OP_LABEL:
            fprintf(ir_out, "label%d ", op->u.label_no);
            break;
        case OP_TEMP:
            fprintf(ir_out, "t%d ", op->u.temp_no);
            break;
        case OP_CONSTANT:
            fprintf(ir_out, "#%lld ", op->u.const_val);
            break;
        default:
            assert(0);
            break;
    }
}

void show_ir(InterCode ir, FILE* ir_out) {
    if (ir == NULL || ir_out == NULL) return;
    switch (ir->kind) {
        case IR_LABEL:
            fprintf(ir_out, "LABEL ");
            show_op(ir->u.singleop.op, ir_out);
            fprintf(ir_out, ": ");
            break;
        case IR_FUNC:
            fprintf(ir_out, "FUNCTION ");
            show_op(ir->u.singleop.op, ir_out);
            fprintf(ir_out, ": ");
            break;
        case IR_GOTO:
            fprintf(ir_out, "GOTO ");
            show_op(ir->u.singleop.op, ir_out);
            break;
        case IR_RETURN:
            fprintf(ir_out, "RETURN ");
            show_op(ir->u.singleop.op, ir_out);
            break;
        case IR_ARG:
            fprintf(ir_out, "ARG ");
            show_op(ir->u.singleop.op, ir_out);
            break;
        case IR_PARAM:
            fprintf(ir_out, "PARAM ");
            show_op(ir->u.singleop.op, ir_out);
            break;
        case IR_READ:
            fprintf(ir_out, "READ ");
            show_op(ir->u.singleop.op, ir_out);
            break;
        case IR_WRITE:
            fprintf(ir_out, "WRITE ");
            show_op(ir->u.singleop.op, ir_out);
            break;
        case IR_DEC:
            fprintf(ir_out, "DEC ");
            show_op(ir->u.dec.op, ir_out);
            fprintf(ir_out, "%d ", ir->u.dec.size);
            break;
        case IR_ASSIGN:
            show_op(ir->u.binop.left, ir_out);
            fprintf(ir_out, ":= ");
            show_op(ir->u.binop.right, ir_out);
            break;
        case IR_ADDR:
            show_op(ir->u.binop.left, ir_out);
            fprintf(ir_out, ":= &");
            show_op(ir->u.binop.right, ir_out);
            break;
        case IR_LOAD:
            show_op(ir->u.binop.left, ir_out);
            fprintf(ir_out, ":= *");
            show_op(ir->u.binop.right, ir_out);
            break;
        case IR_STORE:
            fprintf(ir_out, "*");
            show_op(ir->u.binop.left, ir_out);
            fprintf(ir_out, ":= ");
            show_op(ir->u.binop.right, ir_out);
            break;
        case IR_CALL:
            show_op(ir->u.binop.left, ir_out);
            fprintf(ir_out, ":= CALL ");
            show_op(ir->u.binop.right, ir_out);
            break;
        case IR_ADD:
            show_op(ir->u.tripleop.res, ir_out);
            fprintf(ir_out, ":= ");
            show_op(ir->u.tripleop.op1, ir_out);
            fprintf(ir_out, "+ ");
            show_op(ir->u.tripleop.op2, ir_out);
            break;
        case IR_SUB:
            show_op(ir->u.tripleop.res, ir_out);
            fprintf(ir_out, ":= ");
            show_op(ir->u.tripleop.op1, ir_out);
            fprintf(ir_out, "- ");
            show_op(ir->u.tripleop.op2, ir_out);
            break;
        case IR_MUL:
            show_op(ir->u.tripleop.res, ir_out);
            fprintf(ir_out, ":= ");
            show_op(ir->u.tripleop.op1, ir_out);
            fprintf(ir_out, "* ");
            show_op(ir->u.tripleop.op2, ir_out);
            break;
        case IR_DIV:
            show_op(ir->u.tripleop.res, ir_out);
            fprintf(ir_out, ":= ");
            show_op(ir->u.tripleop.op1, ir_out);
            fprintf(ir_out, "/ ");
            show_op(ir->u.tripleop.op2, ir_out);
            break;
        case IR_IF_GOTO:
            fprintf(ir_out, "IF ");
            show_op(ir->u.if_goto.x, ir_out);
            fprintf(ir_out, "%s ", ir->u.if_goto.relop);
            show_op(ir->u.if_goto.y, ir_out);
            fprintf(ir_out, "GOTO ");
            show_op(ir->u.if_goto.z, ir_out);
            break;
        default:
            assert(0);
            break;
    }
    fprintf(ir_out, "\n");
}

void show_ir_list(InterCodeList ir_list_head, FILE* ir_out) {
    label_array = (InterCodeList*)malloc(sizeof(InterCodeList) * label_number);
    InterCodeList cur = ir_list_head->next;
    for (int i = 0; i < label_number; i++) label_array[i] = NULL;
    while (cur != ir_list_head) {
        assert(cur->code != NULL);
        show_ir(cur->code, ir_out);
        if (cur->code->kind == IR_LABEL) label_array[cur->code->u.singleop.op->u.label_no] = cur;
        cur = cur->next;
    }
}


InterCode gen_ir(InterCodeList ir_list_head, int ir_kind, Operand op1, Operand op2, Operand op3, int dec_size, char* relop) {
    InterCode res_ir = (InterCode)malloc(sizeof(struct InterCode_));
    res_ir->kind = ir_kind;
    res_ir->bb_start = false;
    switch (ir_kind) {
        case IR_LABEL:
        case IR_FUNC:
        case IR_GOTO:
        case IR_RETURN:
        case IR_ARG:
        case IR_PARAM:
        case IR_READ:
        case IR_WRITE:
            if (op1 == NULL) {
                free(res_ir);
                res_ir = NULL;
            } else {
                res_ir->u.singleop.op = op1;
            }
            break;
        case IR_DEC:
            if (op1 == NULL) {
                free(res_ir);
                res_ir = NULL;
            } else {
                res_ir->u.dec.op = op1;
                res_ir->u.dec.size = dec_size;
            }
            break;
        case IR_ASSIGN:
        case IR_ADDR:
        case IR_LOAD:
        case IR_STORE:
        case IR_CALL:
            if (op1 == NULL || op2 == NULL) {
                free(res_ir);
                res_ir = NULL;
            } else {
                res_ir->u.binop.left = op1;
                res_ir->u.binop.right = op2;
            }
            break;
        case IR_ADD:
        case IR_SUB:
        case IR_MUL:
        case IR_DIV:
            if (op1 == NULL || op2 == NULL || op3 == NULL) {
                free(res_ir);
                res_ir = NULL;
            } else {
                res_ir->u.tripleop.res = op1;
                res_ir->u.tripleop.op1 = op2;
                res_ir->u.tripleop.op2 = op3;
            }
            break;
        case IR_IF_GOTO:
            if (op1 == NULL || op2 == NULL || op3 == NULL) {
                free(res_ir);
                res_ir = NULL;
            } else {
                res_ir->u.if_goto.x = op1;
                res_ir->u.if_goto.y = op2;
                res_ir->u.if_goto.z = op3;
                strcpy(res_ir->u.if_goto.relop, relop);
            }
            break;
        default:
            assert(0);
            break;
    }
    if (ir_list_head) add_ir(ir_list_head, res_ir);
    return res_ir;
}

Operand gen_operand(int operand_kind, long long val, int number, char* name) {
    Operand ret_op = (Operand)malloc(sizeof(struct Operand_));
    ret_op->kind = operand_kind;
    FieldList result;
    switch (operand_kind) {
        case OP_ADDRESS:
            ret_op->u.addr_no = number;
            break;
        case OP_FUNCTION:
            result = query(name);
            assert(result != NULL && result->type->kind == FUNCTION);
            ret_op->u.func_name = name;
            break;
        case OP_ARRAY:
            result = query(name);
            assert(result != NULL && result->type->kind == ARRAY);
            ret_op->u.array_no = result->id;
            break;
        case OP_STRUCTURE:
            break;
        case OP_VARIABLE:
            result = query(name);
            assert(result != NULL && result->type->kind == BASIC);
            ret_op->u.var_no = result->id;
            break;
        case OP_LABEL:
            ret_op->u.label_no = number;
            break;
        case OP_TEMP:
            ret_op->u.temp_no = number;
            break;
        case OP_CONSTANT:
            ret_op->u.const_val = val;
            break;
        default:
            assert(0);
            break;
    }
    return ret_op;
}

Operand op_temp() { return gen_operand(OP_TEMP, -1, temp_number++, NULL); }
Operand op_addr() { return gen_operand(OP_ADDRESS, -1, addr_number++, NULL); }
Operand op_label() { return gen_operand(OP_LABEL, -1, label_number++, NULL); }

Operand get_addr(Operand addr, bool is_arg) {
    if (addr->kind != OP_ARRAY) return addr;
    Operand place = op_addr();
    // place := &addr
    gen_ir(IrList, IR_ADDR, place, addr, NULL, -1, NULL);
    return place;
}

int  calculate_size(Type type) {
    if (type == NULL) return 0;
    if (type->kind == BASIC) {
        return 4;
    } else if (type->kind == ARRAY) {
        return type->u.array.size *  calculate_size(type->u.array.elem);
    } else if (type->kind == STRUCTURE) {
        int size = 0;
        FieldList iter = type->u.structfield->type->u.member;
        while (iter) {
            size +=  calculate_size(iter->type);
            iter = iter->tail;
        }
        return size;

    } else {
        assert(0);
    }
    return 0;
}

Operand copy_array(Operand op_left, Operand op_right) {
    Operand left_base = get_addr(op_left, false);
    Operand right_base = get_addr(op_right, false);

    int size_left =  calculate_size(op_left->type) * op_left->size;
    int size_right =  calculate_size(op_right->type) * op_right->size;
    int size = size_left < size_right ? size_left : size_right;
    assert(size % 4 == 0);
    Operand left = op_addr();
    Operand right = op_addr();
    Operand val = op_temp();
    // val := *right
    gen_ir(IrList, IR_LOAD, val, right_base, NULL, -1, NULL);
    // *left := val
    gen_ir(IrList, IR_STORE, left_base, val, NULL, -1, NULL);
    for (int i = 4; i < size; i += 4) {
        Operand offset = gen_operand(OP_CONSTANT, i, -1, NULL);
        // left := base + offset
        gen_ir(IrList, IR_ADD, left, left_base, offset, -1, NULL);
        // right := base + offset
        gen_ir(IrList, IR_ADD, right, right_base, offset, -1, NULL);
        // val := *right
        gen_ir(IrList, IR_LOAD, val, right, NULL, -1, NULL);
        // *left := val
        gen_ir(IrList, IR_STORE, left, val, NULL, -1, NULL);
    }
    return left_base;
}

Operand load_value(Operand addr) {
    if (addr->kind != OP_ADDRESS) return addr;
    Operand place = op_temp();
    // place := *addr
    gen_ir(IrList, IR_LOAD, place, addr, NULL, -1, NULL);
    return place;
}

void translate_Program(TreeNode root) {
    IrList = init_ir_list();
    assert(IrList != NULL);
    if (root == NULL) return;
    // Program -> ExtDefList
    assert(root->children_num == 1);
    translate_ExtDefList(get_child(root, 0));
}

void translate_ExtDefList(TreeNode root) {
    if (root == NULL) return;
    // ExtDefList -> ExtDef ExtDefList
    assert(root->children_num == 2);
    translate_ExtDef(get_child(root, 0));
    translate_ExtDefList(get_child(root, 1));
}

void translate_ExtDef(TreeNode root) {
    if (root == NULL) return;
    assert(root->children_num == 2 || root->children_num == 3);
    if (root->children_num == 3) {
        if (strcmp(get_child(root, 1)->name, "ExtDecList") == 0) {  
            // ExtDef -> Specifier ExtDecList SEMI
        } 
        else if (strcmp(get_child(root, 2)->name, "CompSt") == 0) {
            translate_FunDec(get_child(root, 1));
            translate_CompSt(get_child(root, 2));
        }
    } 
    else if (root->children_num == 2) {
        if (strcmp(get_child(root, 1)->name, "SEMI") == 0) { 
            // ExtDef -> Specifier SEMI
        }
    }
}

Operand translate_VarDec(TreeNode root) {
    if (root == NULL) return NULL;
    assert(root->children_num == 1 || root->children_num == 4);
    Operand name_op = NULL;
    if (root->children_num == 1) {  
        // VarDec -> ID
        char* var_name = get_child(root, 0)->val;
        FieldList res = query(var_name);
        assert(res != NULL);
        if (res->type->kind == ARRAY) {  
            name_op = gen_operand(OP_ARRAY, -1, -1, var_name);
            name_op->type = res->type->u.array.elem;
            name_op->size = res->type->u.array.size;
            int dec_size =  calculate_size(res->type);
            // DEC variable.name size
            gen_ir(IrList, IR_DEC, name_op, NULL, NULL, dec_size, NULL);
        } 
        else if (res->type->kind == BASIC) {  
            name_op = gen_operand(OP_VARIABLE, -1, -1, var_name);
        } 
        else if (res->type->kind == STRUCTURE) { 
        } 
        else {
            assert(0);
        }
    } 
    else if (root->children_num == 4) {  
        // VarDec -> VarDec LB INT RB
        return translate_VarDec(get_child(root, 0));
    }
    return name_op;
}

void translate_FunDec(TreeNode root) {
    if (root == NULL) return;
    assert(root->children_num == 3 || root->children_num == 4);
    char* func_name = get_child(root, 0)->val;
    FieldList func_field = query(func_name);
    assert(func_field != NULL);
    // FUNCTION func.name
    Operand func_op = gen_operand(OP_FUNCTION, -1, -1, func_name);
    gen_ir(IrList, IR_FUNC, func_op, NULL, NULL, -1, NULL);
    if (root->children_num == 3) {         
        // FunDec -> ID LP RP
    } 
    else if (root->children_num == 4) {  
        // FunDec -> ID LP VarList RP
        FieldList arg_field = func_field->type->u.function.params;
        while (arg_field) {
            // PARAM arg.name
            Operand arg_op;
            switch (arg_field->type->kind) {
                case BASIC:
                    arg_op = gen_operand(OP_VARIABLE, -1, -1, arg_field->name);
                    break;
                case ARRAY:
                    arg_op = gen_operand(OP_ARRAY, -1, -1, arg_field->name);
                    break;
                case STRUCTURE: 
                    break;
                default:
                    break;
            }
            gen_ir(IrList, IR_PARAM, arg_op, NULL, NULL, -1, NULL);
            arg_field = arg_field->tail;
        }
    }
}

void translate_CompSt(TreeNode root) {
    if (root == NULL) return;
    // CompSt -> LC DefList StmtList RC
    assert(root->children_num == 4);
    translate_DefList(get_child(root, 1));
    translate_StmtList(get_child(root, 2));
}

void translate_StmtList(TreeNode root) {
    if (root == NULL) return;
    // Stmtlist -> Stmt Stmtlist
    assert(root->children_num == 2);
    translate_Stmt(get_child(root, 0));
    translate_StmtList(get_child(root, 1));
}

void translate_Stmt(TreeNode root) {
    if (root == NULL) return;
    assert(root->children_num == 1 || root->children_num == 2 || root->children_num == 3 || root->children_num == 5 ||
           root->children_num == 7);
    if (root->children_num == 1) { 
         // Stmt -> CompSt
        translate_CompSt(get_child(root, 0));
    } 
    else if (root->children_num == 2) { 
         // Stmt -> Exp SEMI
        translate_Exp(get_child(root, 0), op_temp());
    } 
    else if (root->children_num == 3) {  
        // Stmt -> RETURN Exp SEMI
        Operand t1 = op_temp();
        translate_Exp(get_child(root, 1), t1);
        t1 = load_value(t1);
        // RETURN t1
        gen_ir(IrList, IR_RETURN, t1, NULL, NULL, -1, NULL);
    } 
    else if (root->children_num == 5) {
        if (strcmp(get_child(root, 0)->name, "IF") == 0) {  
            // Stmt -> IF LP Exp RP Stmt
            Operand label1 = op_label();
            Operand label2 = op_label();
            translate_Cond(get_child(root, 2), label1, label2);
            // LABEL label1
            gen_ir(IrList, IR_LABEL, label1, NULL, NULL, -1, NULL);
            translate_Stmt(get_child(root, 4));
            // LABEL label2
            gen_ir(IrList, IR_LABEL, label2, NULL, NULL, -1, NULL);
        } 
        else if (strcmp(get_child(root, 0)->name, "WHILE") == 0) {  
            // Stmt -> WHILE LP Exp RP Stmt
            Operand label1 = op_label();
            Operand label2 = op_label();
            Operand label3 = op_label();
            // LABEL label1
            gen_ir(IrList, IR_LABEL, label1, NULL, NULL, -1, NULL);
            translate_Cond(get_child(root, 2), label2, label3);
            // LABEL label2
            gen_ir(IrList, IR_LABEL, label2, NULL, NULL, -1, NULL);
            translate_Stmt(get_child(root, 4));
            // GOTO label1
            gen_ir(IrList, IR_GOTO, label1, NULL, NULL, -1, NULL);
            // LABEL label3
            gen_ir(IrList, IR_LABEL, label3, NULL, NULL, -1, NULL);
        }
    } 
    else if (root->children_num == 7) {  
        // Stmt -> IF LP Exp RP Stmt ELSE Stmt
        Operand label1 = op_label();
        Operand label2 = op_label();
        Operand label3 = op_label();
        // tree_display(get_child(root, 2), 0);
        translate_Cond(get_child(root, 2), label1, label2);
        // LABEL label1
        gen_ir(IrList, IR_LABEL, label1, NULL, NULL, -1, NULL);
        translate_Stmt(get_child(root, 4));
        // GOTO label3
        gen_ir(IrList, IR_GOTO, label3, NULL, NULL, -1, NULL);
        // LABEL label2
        gen_ir(IrList, IR_LABEL, label2, NULL, NULL, -1, NULL);
        translate_Stmt(get_child(root, 6));
        // LABEL label3
        gen_ir(IrList, IR_LABEL, label3, NULL, NULL, -1, NULL);
    }
}

void translate_DefList(TreeNode root) {
    if (root == NULL) return;
    // DefList -> Def DefList
    assert(root->children_num == 2);
    translate_Def(get_child(root, 0));
    translate_DefList(get_child(root, 1));
}

void translate_Def(TreeNode root) {
    if (root == NULL) return;
    // Def -> Specifier DecList SEMI
    assert(root->children_num == 3);
    translate_DecList(get_child(root, 1));
}

void translate_DecList(TreeNode root) {
    if (root == NULL) return;
    assert(root->children_num == 1 || root->children_num == 3);
    translate_Dec(get_child(root, 0));
    if (root->children_num == 1) {         
        // DecList -> Dec
    } 
    else if (root->children_num == 3) {  
        // DecList -> Dec COMMA DecList
        translate_DecList(get_child(root, 2));
    }
}

void translate_Dec(TreeNode root) {
    if (root == NULL) return;
    assert(root->children_num == 1 || root->children_num == 3);
    Operand name_op = translate_VarDec(get_child(root, 0));
    if (root->children_num == 1) {         
        // Dec -> VarDec
    } 
    else if (root->children_num == 3) {  
        // VarDec ASSIGNOP Exp
        Operand t1 = op_temp();
        translate_Exp(get_child(root, 2), t1);
        if (name_op->kind == OP_ARRAY) {
            copy_array(name_op, t1);
        } 
        else if (name_op->kind == OP_VARIABLE) {
            t1 = load_value(t1);
            // variable.name := t1
            gen_ir(IrList, IR_ASSIGN, name_op, t1, NULL, -1, NULL);
        }
    }
}

void translate_Exp(TreeNode root, Operand place) {
    if (root == NULL) return;
    assert(root->children_num == 1 || root->children_num == 2 || root->children_num == 3 || root->children_num == 4);
    if ((root->children_num == 2 && strcmp(get_child(root, 0)->name, "NOT") == 0) ||
        (root->children_num == 3 &&
         (strcmp(get_child(root, 1)->name, "AND") == 0 || strcmp(get_child(root, 1)->name, "OR") == 0 ||
          strcmp(get_child(root, 1)->name, "RELOP") == 0))) {
        /*Exp -> NOT Exp
            Exp -> Exp RELOP Exp
            Exp -> Exp AND Exp
            Exp -> Exp OR Exp*/
        Operand label1 = op_label();
        Operand label2 = op_label();
        // place := #0
        gen_ir(IrList, IR_ASSIGN, place, gen_operand(OP_CONSTANT, 0, -1, NULL), NULL, -1, NULL);
        translate_Cond(root, label1, label2);
        // LABEL label1
        gen_ir(IrList, IR_LABEL, label1, NULL, NULL, -1, NULL);
        // place := #1
        gen_ir(IrList, IR_ASSIGN, place, gen_operand(OP_CONSTANT, 1, -1, NULL), NULL, -1, NULL);
        // LABEL label2
        gen_ir(IrList, IR_LABEL, label2, NULL, NULL, -1, NULL);
    } else if (root->children_num == 1) {
        if (strcmp(get_child(root, 0)->name, "ID") == 0) {  
            // Exp -> ID
            FieldList result = query(get_child(root, 0)->val);
            assert(result != NULL);
            if (result->type->kind == BASIC) {
                // place := variable.name
                place->kind = OP_VARIABLE;
                place->u.var_no = result->id;
            } else if (result->type->kind == ARRAY) {
                // ID type : ARRAY TODO
                Operand array = gen_operand(OP_ARRAY, -1, -1, result->name);
                if (result->arg == true) {
                    place->kind = OP_ADDRESS;
                    place->u.addr_no = addr_number++;
                    // place := array
                    gen_ir(IrList, IR_ASSIGN, place, array, NULL, -1, NULL);
                } else {
                    place->kind = OP_ARRAY;
                    place->u.array_no = result->id;
                }
                place->type = result->type->u.array.elem;
                place->size = result->type->u.array.size;
            } 
            else if (result->type->kind == STRUCTURE) { assert(0); }
        } 
        else if (strcmp(get_child(root, 0)->name, "INT") == 0) {  
            // Exp -> INT
            // place := #value
            place->kind = OP_CONSTANT;
            place->u.const_val = get_child(root, 0)->data.val_int;
        } 
        else {
            assert(0);
        }
    } 
    else if (root->children_num == 2) {
        if (strcmp(get_child(root, 0)->name, "MINUS") == 0) {  
            // Exp -> MINUS Exp
            Operand t1 = op_temp();
            translate_Exp(get_child(root, 1), t1);
            t1 = load_value(t1);
            if (t1->kind == OP_CONSTANT) {
                place->kind = OP_CONSTANT;
                place->u.const_val = -1 * t1->u.const_val;
            } 
            else {  // place := #0 - t1
                gen_ir(IrList, IR_SUB, place, gen_operand(OP_CONSTANT, 0, -1, NULL), t1, -1, NULL);
            }
        }
    } 
    else if (root->children_num == 3) {
        if (strcmp(get_child(root, 0)->name, "LP") == 0) {  
            // Exp -> LP Exp RP
            translate_Exp(get_child(root, 1), place);
        } else if (strcmp(get_child(root, 0)->name, "ID") == 0) {  
            // Exp -> ID LP RP
            FieldList function = query(get_child(root, 0)->val);
            assert(function != NULL);
            if (strcmp(function->name, "read") == 0) {
                // READ place
                gen_ir(IrList, IR_READ, place, NULL, NULL, -1, NULL);
            } 
            else {
                // place := CALL function.name
                Operand func_op = gen_operand(OP_FUNCTION, -1, -1, function->name);
                gen_ir(IrList, IR_CALL, place, func_op, NULL, -1, NULL);
            }
        } 
        else if (strcmp(get_child(root, 1)->name, "DOT") == 0) {  
            // Exp -> Exp DOT ID
        } 
        else if (strcmp(get_child(root, 1)->name, "ASSIGNOP") == 0) {  
            // Exp ASSIGNOP Exp
            Operand op_left = op_temp();
            translate_Exp(get_child(root, 0), op_left);
            Operand op_right = op_temp();
            translate_Exp(get_child(root, 2), op_right);
            if (op_left->kind == OP_ADDRESS || op_left->kind == OP_ARRAY) {
                if (op_right->kind == OP_ADDRESS || op_right->kind == OP_ARRAY) {
                    copy_array(op_left, op_right);
                } 
                else { 
                    assert(op_left->kind == OP_ADDRESS);
                    // *op_left := op_right
                    gen_ir(IrList, IR_STORE, op_left, op_right, NULL, -1, NULL);
                }
            }
            else {
                op_right = load_value(op_right);
                // op_left := op_right
                gen_ir(IrList, IR_ASSIGN, op_left, op_right, NULL, -1, NULL);
            }
            // place := op_right
            place->kind = op_right->kind;
            place->u = op_right->u;
        } 
        else {
            /*Exp -> Exp PLUS Exp
                Exp -> Exp MINUS Exp
                Exp -> Exp STAR Exp
                Exp -> Exp DIV Exp*/
            Operand t1 = op_temp();
            translate_Exp(get_child(root, 0), t1);
            t1 = load_value(t1);
            Operand t2 = op_temp();
            translate_Exp(get_child(root, 2), t2);
            t2 = load_value(t2);
            int ir_kind = -1;
            long long val;
            if (strcmp(get_child(root, 1)->name, "PLUS") == 0) {
                ir_kind = IR_ADD;
                val = t1->u.const_val + t2->u.const_val;
            } 
            else if (strcmp(get_child(root, 1)->name, "MINUS") == 0) {
                ir_kind = IR_SUB;
                val = t1->u.const_val - t2->u.const_val;
            } 
            else if (strcmp(get_child(root, 1)->name, "STAR") == 0) {
                ir_kind = IR_MUL;
                val = t1->u.const_val * t2->u.const_val;
            } 
            else if (strcmp(get_child(root, 1)->name, "DIV") == 0) {
                ir_kind = IR_DIV;
                long long lhsVal = t1->u.const_val;
                long long rhsVal = t2->u.const_val;
                if (lhsVal < 0 && rhsVal > 0) {
                    val = (lhsVal - rhsVal + 1) / rhsVal;
                } 
                else if (lhsVal > 0 && rhsVal < 0) {
                    val = (lhsVal - rhsVal - 1) / rhsVal;
                } 
                else {
                    val = rhsVal ? lhsVal / rhsVal : 0;
                }
            } else {
                assert(0);
            }
            if (t1->kind == OP_CONSTANT && t2->kind == OP_CONSTANT) {
                place->kind = OP_CONSTANT;
                place->u.const_val = val;
            } 
            else {
                // place := t1 op t2
                gen_ir(IrList, ir_kind, place, t1, t2, -1, NULL);
            }
        }
    } 
    else if (root->children_num == 4) {
        if (strcmp(get_child(root, 0)->name, "ID") == 0) {  
            // Exp -> ID LP Args RP
            FieldList function = query(get_child(root, 0)->val);
            assert(function != NULL);
            if (strcmp(function->name, "write") == 0) {
                translate_Args(get_child(root, 2), true);
                // place := #0
                place->kind = OP_CONSTANT;
                place->u.const_val = 0;
            } 
            else {
                translate_Args(get_child(root, 2), false);
                // place := CALL function.name
                Operand func_op = gen_operand(OP_FUNCTION, -1, -1, function->name);
                gen_ir(IrList, IR_CALL, place, func_op, NULL, -1, NULL);
            }
        } 
        else if (strcmp(get_child(root, 0)->name, "Exp") == 0) {  
            // Exp -> Exp LB Exp RB
            Operand t1 = op_temp();
            translate_Exp(get_child(root, 0), t1);
            assert(t1->kind == OP_ARRAY || t1->kind == OP_ADDRESS);
            Operand t2 = op_temp();
            translate_Exp(get_child(root, 2), t2);
            t2 = load_value(t2);
            Operand offset = op_temp();
            int width =  calculate_size(t1->type);
            if (t2->kind == OP_CONSTANT) {
                offset->kind = OP_CONSTANT;
                offset->u.const_val = width * t2->u.const_val;
            } 
            else {
                // offset :=  t2 * width
                gen_ir(IrList, IR_MUL, offset, t2, gen_operand(OP_CONSTANT, width, -1, NULL), -1, NULL);
            }

            place->kind = OP_ADDRESS;
            place->u.addr_no = addr_number++;

            if (t1->kind == OP_ARRAY) {  
                // Exp1-> ID
                if (offset->kind == OP_CONSTANT && offset->u.const_val == 0) {
                    gen_ir(IrList, IR_ADDR, place, t1, NULL, -1, NULL);
                } else {
                    Operand base = op_addr();
                    // base := &addr
                    gen_ir(IrList, IR_ADDR, base, t1, NULL, -1, NULL);
                    // place := base + offset
                    gen_ir(IrList, IR_ADD, place, base, offset, -1, NULL);
                }
            } else if (t1->kind == OP_ADDRESS) {  
                // Exp1 -> Exp LB Exp RB
                // place := t1 + offset
                gen_ir(IrList, IR_ADD, place, t1, offset, -1, NULL);
            } else {
                assert(0);
            }

            if (t1->type->kind == BASIC) {
                place->type = NULL;
                place->size = 0;
            } 
            else if (t1->type->kind == ARRAY) {
                place->type = t1->type->u.array.elem;
                place->size = t1->type->u.array.size;
            }
        }
    }
}

void translate_Args(TreeNode root, bool write_func) {
    if (root == NULL) return;
    assert(root->children_num == 1 || root->children_num == 3);
    if (root->children_num == 1) {         
        // Args -> Exp
    } 
    else if (root->children_num == 3) {  
        // Args -> Exp COMMA Args
        translate_Args(get_child(root, 2), write_func);
    }
    Operand arg = op_temp();
    translate_Exp(get_child(root, 0), arg);
    if (arg->kind == OP_STRUCTURE) {}
    if (write_func) {  // WRITE arg
        arg = load_value(arg);
        gen_ir(IrList, IR_WRITE, arg, NULL, NULL, -1, NULL);
    } 
    else {
        if (arg->kind == OP_ARRAY) {
            arg = get_addr(arg, true);
        } 
        else if (arg->kind == OP_ADDRESS) {
            if (arg->type == NULL) { 
                arg = load_value(arg);
            } 
            else if (arg->type->kind == BASIC) {
            } 
        }
        gen_ir(IrList, IR_ARG, arg, NULL, NULL, -1, NULL);
    }
}

void translate_Cond(TreeNode root, Operand label_true, Operand label_false) {
    if (root == NULL) return;
    assert(root->children_num == 1 || root->children_num == 2 || root->children_num == 3 || root->children_num == 4);

    if (root->children_num == 2 && strcmp(get_child(root, 0)->name, "NOT") == 0) {  
        // NOT Exp
        translate_Cond(get_child(root, 1), label_false, label_true);
    } 
    else if (root->children_num == 3 && strcmp(get_child(root, 1)->name, "AND") == 0) {  
        // Exp AND Exp
        Operand label1 = op_label();
        translate_Cond(get_child(root, 0), label1, label_false);
        gen_ir(IrList, IR_LABEL, label1, NULL, NULL, -1, NULL);
        translate_Cond(get_child(root, 2), label_true, label_false);
    } 
    else if (root->children_num == 3 && strcmp(get_child(root, 1)->name, "OR") == 0) {  
        // Exp OR Exp
        Operand label1 = op_label();
        translate_Cond(get_child(root, 0), label_true, label1);
        gen_ir(IrList, IR_LABEL, label1, NULL, NULL, -1, NULL);
        translate_Cond(get_child(root, 2), label_true, label_false);
    } 
    else if (root->children_num == 3 && strcmp(get_child(root, 1)->name, "RELOP") == 0) {  
        // Exp RELOP Exp
        Operand t1 = op_temp();
        translate_Exp(get_child(root, 0), t1);
        t1 = load_value(t1);
        Operand t2 = op_temp();
        translate_Exp(get_child(root, 2), t2);
        t2 = load_value(t2);
        char* relop = get_child(root, 1)->val;
        // IF t1 op t2 GOTO label_true
        gen_ir(IrList, IR_IF_GOTO, t1, t2, label_true, -1, relop);
        // GOTO label_false
        gen_ir(IrList, IR_GOTO, label_false, NULL, NULL, -1, NULL);
    } 
    else {
        Operand t1 = op_temp();
        translate_Exp(root, t1);
        t1 = load_value(t1);
        // IF t1 != #0 GOTO label_true
        gen_ir(IrList, IR_IF_GOTO, t1, gen_operand(OP_CONSTANT, 0, -1, NULL), label_true, -1, "!=");
        // GOTO label_false
        gen_ir(IrList, IR_GOTO, label_false, NULL, NULL, -1, NULL);
    }
}