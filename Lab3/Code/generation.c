#include "generation.h"

#define TYPE_VAR 1
#define TYPE_TEMP 2
#define TYPE_LABEL 3

InterCodes codes;
static struct Param *currentParams;

char *newVar(int type){
	char inf;
	static int cntvar = 0, cnttemp = 0, cntlabel = 0;
	int n;
	switch((int)type)
	{
	case TYPE_VAR: 
        inf = 'v'; 
        n = cntvar++; 
        break;
	case TYPE_TEMP: 
        inf = 't'; 
        n = cnttemp++; 
        break;
	case TYPE_LABEL: 
        inf = 'L'; 
        n = cntlabel++; 
        break;
    default:
        printf("No match case in func new.\n");
        break;
	}
	char *ret;
	sprintf(ret, "%c%d%c", inf, n, '\0');
	return ret;
}

Operand Operand_(enum OPERAND_KIND kind, enum TYPE type){
	Operand op = (Operand )malloc(sizeof(struct Operand_));
	memset(op, 0, sizeof(op));
	op->kind = kind;
	op->type = type;
	return op;
}

Operand op_constant(int value){
	Operand op = Operand_(CONSTANT, NORMAL);
    op->u.value = value;
	return op;
}

Operand op_var(enum OPERAND_KIND kind, enum TYPE type, char *str)
{
	Operand op = Operand_(kind, type);
    op->u.str = str;
	return op;
}

Operand op_copy(Operand operand){
	Operand op = Operand_(operand->kind, operand->type);
	if(operand->kind == CONSTANT) op->u.value = operand->u.value;
	else op->u.str = operand->u.str;
	return op;
}

Arg Arg_(Operand var){
	Arg arg_ = (Arg )malloc(sizeof(struct Arg_));
	arg_->arg = var;
	arg_->next = NULL;
	return arg_;
}

Arg insert_arg(Arg args, Operand operand){
	if(!args) args = Arg_(operand);
	else{
		Arg a = Arg_(operand);
		a->next = args;
		args = a;
	}
	return args;
}

void insert_param(char *str){
	struct Param *param = (struct Param *)malloc(sizeof(struct Param));
	param->var = str;
	param->next = NULL;
	if(!currentParams) currentParams = param;
	else{
		param->next = currentParams;
		currentParams = param;
	}
}

bool in_params(char *str){
	struct Param *p = currentParams;
	while(p){
		if(strcmp(p->var, str) == 0) return true;
		p = p->next;
	}
	return false;
}

InterCode InterCode_(enum INTER_CODE_KIND kind){
	InterCode c = (InterCode)malloc(sizeof(struct InterCode_));
	c->kind = kind;
	return c;
}

InterCode singleOp(enum INTER_CODE_KIND kind, Operand operand) {
	InterCode c = InterCode_(kind);
	c->u.singleop.op = operand;
	return c;
}

InterCode binOp(enum INTER_CODE_KIND kind, Operand dest, Operand src) {
	InterCode c  = InterCode_(kind);
    c->u.binop.dest = dest;
	c->u.binop.src = src;
	return c;	
}

InterCode tripleOp(enum INTER_CODE_KIND kind, Operand dest, Operand op1, Operand op2) {
	InterCode c  = InterCode_(kind);
    c->u.tripleop.dest = dest;
    c->u.tripleop.op1 = op1;
	c->u.tripleop.op2 = op2;
	return c;
}

InterCode if_goto(Operand op1, Operand op2, Operand dest, char *relop) {
    InterCode c  = InterCode_(IF_GOTO_);
	c->u.if_goto.op1 = op1;
    c->u.if_goto.op2 = op2;
    c->u.if_goto.dest = dest;
    c->u.if_goto.relop = relop;
	return c;
}

InterCode dec(Operand var, int size){
	InterCode c = InterCode_(DEC_);
    c->u.dec.var = var;
	c->u.dec.size = size;
	return c;
}

InterCodes init_node() {
	InterCodes clist = (InterCodes)malloc(sizeof(struct InterCodes_));
    clist->code = NULL;
    clist->prev = clist;
    clist->next = clist;
	return clist;
}


void insert_code( InterCode c) {
	InterCodes node = init_node();
	node->code = c;
    node->prev = codes->prev;
	node->next = codes;
    codes->prev->next = node;
    codes->prev = node;
}

void write_op(Operand op, FILE *output){
    // constant value
	if(op->kind == CONSTANT) fprintf(output, "#%d", op->u.value);
    // & or *
	else {
		if(op->type == ADDRESS) fprintf(output, "&");
		else if(op->type == STAR) fprintf(output, "*");
		fprintf(output, "%s", op->u.str);
	}
}

void write_code(InterCode c, FILE *output) {
	switch(c->kind){
	case LABEL_: case FUNC_: case PARAM_:case RETURN_:
	case GOTO_: case ARG_: case READ_: case WRITE_:
		switch(c->kind){
		case LABEL_: fprintf(output, "LABEL ");break;
		case FUNC_: fprintf(output, "FUNCTION "); break;
		case PARAM_: fprintf(output, "PARAM "); break;
		case RETURN_: fprintf(output, "RETURN "); break;
		case GOTO_: fprintf(output, "GOTO "); break;
		case ARG_: fprintf(output, "ARG "); break;
		case READ_: fprintf(output, "READ "); break;
		case WRITE_: fprintf(output, "WRITE "); break;
		}
		write_op(c->u.singleop.op, output);
		if(c->kind == LABEL_ || c->kind == FUNC_) fprintf(output, " :");
		break;
	case DEC_: 
		fprintf(output, "DEC "); 
		write_op(c->u.dec.var, output); 
		fprintf(output, " %d", c->u.dec.size); 
        break;
	case ASSIGN_: case CALL_:
		write_op(c->u.binop.dest, output); 
		fprintf(output, " := "); 
		if(c->kind == CALL_) fprintf(output, "CALL ");
		write_op(c->u.binop.src, output);break;
	case ADD_: case SUB_: case MUL_: case DIV_: 
		write_op(c->u.tripleop.dest, output); 
		fprintf(output, " := "); 
		write_op(c->u.tripleop.op1, output); 
		switch(c->kind){
		case ADD_: fprintf(output, " + "); break;
		case SUB_: fprintf(output, " - "); break;
		case MUL_: fprintf(output, " * "); break;
		case DIV_: fprintf(output, " / "); break;
		}
		write_op(c->u.tripleop.op2, output); 
		break;
	case IF_GOTO_:
		fprintf(output, "IF ");
		write_op(c->u.if_goto.op1, output);
		fprintf(output, " %s ", c->u.if_goto.relop);
		write_op(c->u.if_goto.op2, output);
		fprintf(output, " GOTO ");
		write_op(c->u.if_goto.dest, output);
	default: break;
    }
	fprintf(output, "\n");
}

int calculate_width(Type t) {
	if(t->kind == BASIC){
		t->width = 4;
		return 4;
	}
	t->width = t->u.array.size * calculate_width(t->u.array.elem);
	return t->width;
}

void translate_Cond(struct TreeNode *root, Operand label_true, Operand label_false){
	// Exp1 RELOP Exp 2
	if(root->children_num == 3 && strcmp(root->children[1]->name, "RELOP") == 0){
		Operand t1 = op_var(VARIABLE, NORMAL, newVar(TYPE_TEMP));
		Operand t2 = op_var(VARIABLE, NORMAL, newVar(TYPE_TEMP));
		translate_Exp(root->children[0], t1);
		translate_Exp(root->children[2], t2);
		char *Relop = root->children[1]->val_str;
		insert_code(if_goto(t1, t2, label_true, Relop));
		insert_code(singleOp(GOTO_, label_false));
	}
	// Exp1 AND Exp2
	else if(root->children_num == 3 && strcmp(root->children[1]->name, "AND") == 0){
		Operand label1 = op_var(VARIABLE, NORMAL, newVar(TYPE_LABEL));
		translate_Cond(root->children[0], label1, label_false);
		insert_code(singleOp(LABEL_, label1));
		translate_Cond(root->children[2], label_true, label_false);
	}
	// Exp1 OR Exp2
	else if(root->children_num == 3 && strcmp(root->children[1]->name, "OR") == 0){
		Operand label1 = op_var(VARIABLE, NORMAL, newVar(TYPE_LABEL));
		translate_Cond(root->children[0], label_true, label1);
		insert_code(singleOp(LABEL_, label1));
		translate_Cond(root->children[2], label_true, label_false);
	}
	// NOT Exp1
	else if(root->children_num == 2 && strcmp(root->children[0]->name, "NOT") == 0){
		translate_Cond(root->children[1], label_false, label_true);
	}
	// (other cases)
	else{
		Operand t1 = op_var(VARIABLE, NORMAL, newVar(TYPE_TEMP));
		Operand zero = op_constant(0);
		translate_Exp(root, t1);
		insert_code(if_goto(t1, zero, label_true, "!="));
		insert_code(singleOp(GOTO_, label_false));
	}
}

Arg translate_Args(struct TreeNode *root, Arg args){
	// Exp
	Operand t = op_var(VARIABLE, NORMAL, newVar(TYPE_TEMP));
	translate_Exp(root->children[0], t);
	args = insert_arg(args, t);
	// Exp COMMA Args1
	if(root->children_num == 3) args = translate_Args(root->children[2], args);
	return args;
}


void translate_Func(struct TreeNode *root, Operand place){
	char *fname = root->children[0]->val_str;
	if(strcmp(fname, "read") == 0) insert_code(singleOp(READ_, place));
	else if(strcmp(fname, "write") == 0){
		Operand t = op_var(VARIABLE, NORMAL, newVar(TYPE_TEMP));
		translate_Exp(root->children[2]->children[0], t);
		insert_code(singleOp(WRITE_, t));
	}
	else{
		// FunDec → ID LP VarList RP
		 if(root->children_num == 4) {
			Arg args = NULL;
			args = translate_Args(root->children[2], args);
			while(args) {
				insert_code(singleOp(ARG_, args->arg));
				args = args->next;
			}
		}
		// || ID LP RP
		Operand function = op_var(FUNC, NORMAL, fname);
		if(!place) place = op_var(VARIABLE, NORMAL, newVar(TYPE_TEMP));
		insert_code(binOp(CALL_, place, function));
	}
}

void translate_Arithmetic(struct TreeNode *root, Operand place) {
	Operand t1 = op_var(VARIABLE, NORMAL, newVar(TYPE_TEMP));
	Operand t2 = op_var(VARIABLE, NORMAL, newVar(TYPE_TEMP));
	translate_Exp(root->children[0], t1);
	translate_Exp(root->children[2], t2);
	enum INTER_CODE_KIND  kind;
	char *name = root->children[1]->name;
	if(strcmp(name, "PLUS") == 0) kind = ADD_;
	else if(strcmp(name, "MINUS") == 0) kind = SUB_;
	else if(strcmp(name, "STAR") == 0) kind = MUL_;
	else kind = DIV_;
	insert_code(tripleOp(kind, place, t1, t2));
}

Type translate_Array(struct TreeNode *root, Operand place) {
	static char *var[10];
	static int level = 0;
	Type ret = NULL;
	if(strcmp(root->children[0]->children[0]->name, "ID") == 0){
		struct TreeNode *ID = root->children[0]->children[0];
		FieldList f = query(ID->val_str);
		var[level++] = f->var;
		place->u.str = newVar(TYPE_VAR);
		Operand op = NULL;
		if(strcmp(root->children[2]->children[0]->name, "INT") == 0){
			int value = root->children[2]->children[0]->val_int * f->type->u.array.elem->width;
			op = op_constant(value);
			insert_code(binOp(ASSIGN_, op_copy(place), op));
		}
		else{
			op = op_var(VARIABLE, NORMAL, newVar(TYPE_TEMP));
			translate_Exp(root->children[2], op);
			Operand w = op_constant(f->type->u.array.elem->width);
			insert_code(tripleOp(MUL_, op_copy(place), op, w));
		}
		ret = f->type->u.array.elem;
	}
	else{
		Operand base = Operand_(VARIABLE, NORMAL);
		Type type = translate_Array(root->children[0], base);
		place->u.str = newVar(TYPE_TEMP);

		Operand op = op_var(VARIABLE, NORMAL, newVar(TYPE_TEMP));
		Operand index = op_var(VARIABLE, NORMAL, newVar(TYPE_TEMP));
		Operand width = op_constant(type->u.array.elem->width);
		translate_Exp(root->children[2], index);
		insert_code(tripleOp(MUL_, op, index, width));
		insert_code(tripleOp(ADD_, op_copy(place), base, op));
		ret = type->u.array.elem;
	}
	if(ret->u.basic == 1){
		Operand dest = op_var(VARIABLE, NORMAL, newVar(TYPE_TEMP));
		Operand addr = op_var(VARIABLE, ADDRESS, var[--level]);
		if(in_params(addr->u.str)) addr->type = NORMAL;
		insert_code(tripleOp(ADD_, dest, addr, op_copy(place)));
		place->type = STAR;
		place->u.str = dest->u.str;
	}
	return ret;
}

void translate_Assignop(struct TreeNode *root, Operand place){
	Operand dest = NULL;
	if(root->children[0]->children_num == 1){
		struct TreeNode *ID = root->children[0]->children[0];
		FieldList f = query(ID->val_str);
		dest = op_var(VARIABLE, NORMAL, f->var);
	}
	else{
		dest = op_var(VARIABLE, NORMAL, newVar(TYPE_TEMP));
		translate_Array(root->children[0], dest);
	}
	Operand src = op_var(VARIABLE, NORMAL, newVar(TYPE_TEMP));
	translate_Exp(root->children[2], src);
	insert_code(binOp(ASSIGN_, dest, src));
	if(place) insert_code(binOp(ASSIGN_, place, dest));
}

void translate_Exp(struct TreeNode *root, Operand place)
{
	if(root->children_num == 1){
		// INT
		if(place && strcmp(root->children[0]->name, "INT") == 0){
			Operand src = op_constant(root->children[0]->val_int);
			insert_code(binOp(ASSIGN_, place, src));
		}
		// ID
		else if(place){
			FieldList f = query(root->children[0]->val_str);
			Operand src = op_var(VARIABLE, NORMAL, f->var);
			if(f->type->kind == ARRAY && in_params(f->var) == 0) src->type = ADDRESS;
			insert_code(binOp(ASSIGN_, place, src));
		}
	}
	// Exp1 RELOP Exp 2||  NOT Exp || Exp1 AND Exp 2 || Exp1 OR Exp 2
	else if((root->children_num == 2 && strcmp(root->children[0]->name, "NOT") == 0)
					|| (root->children_num == 3 
					&& (strcmp(root->children[1]->name, "RELOP") == 0 
					|| strcmp(root->children[1]->name, "AND") == 0 
					|| strcmp(root->children[1]->name, "OR") == 0))){
		Operand label1 = op_var(VARIABLE, NORMAL, newVar(TYPE_LABEL));
		Operand	label2 = op_var(VARIABLE, NORMAL, newVar(TYPE_LABEL));
		Operand zero = op_constant(0);
		Operand one = op_constant(1);
		insert_code(binOp(ASSIGN_, place, zero));
		translate_Cond(root, label1, label2);

		insert_code(singleOp(LABEL_, label1));
		insert_code(binOp(ASSIGN_, place, one));
		insert_code(singleOp(LABEL_, label2));
	}
	// MINUS Exp1
	else if(root->children_num == 2){
		Operand zero = op_constant(0);
		Operand t1 = op_var(VARIABLE, NORMAL, newVar(TYPE_TEMP));
		translate_Exp(root->children[1], t1);
		insert_code(tripleOp(SUB_, place, zero, t1));
	}
	// ID LP RP || ID LP Args RP
	else if(strcmp(root->children[1]->name, "LP") == 0) translate_Func(root, place);
	// Exp1 ASSIGNOP Exp2 || Exp1 PLUS Exp2
	else if(root->children_num == 3){
		if(strcmp(root->children[1]->name, "ASSIGNOP") == 0) translate_Assignop(root, place);
		else if(strcmp(root->children[1]->name, "Exp") == 0) translate_Exp(root->children[1], place);
		else translate_Arithmetic(root, place);
	}
	// Array
	else {
		if(strcmp(root->children[0]->name, "Exp") == 0) translate_Array(root, place);	
	}
}

void translate_CompSt(struct TreeNode *root) {
	translate_DefList(root->children[1]);
	struct TreeNode *StmtList = root->children[2];
	while(StmtList->children_num == 2) {
		struct TreeNode *Stmt = StmtList->children[0];
		translate_Stmt(Stmt);
		StmtList = StmtList->children[1];
	}
}

void translate_While(struct TreeNode *root) {
	Operand label1 = op_var(VARIABLE, NORMAL, newVar(TYPE_LABEL));
	Operand label2 = op_var(VARIABLE, NORMAL, newVar(TYPE_LABEL));
	Operand label3 = op_var(VARIABLE, NORMAL, newVar(TYPE_LABEL));
	insert_code(singleOp(LABEL_, label1));
	translate_Cond(root->children[2], label2, label3);
	insert_code(singleOp(LABEL_, label2));
	translate_Stmt(root->children[4]);
	insert_code(singleOp(GOTO_, label1));
	insert_code(singleOp(LABEL_, label3));
}

void translate_Return(struct TreeNode *root) {
	Operand op = op_var(VARIABLE, NORMAL, newVar(TYPE_TEMP));
	translate_Exp(root->children[1], op);
	insert_code(singleOp(RETURN_, op));
}

void translate_If(struct TreeNode *root) {
	Operand label1 = op_var(VARIABLE, NORMAL, newVar(TYPE_LABEL));
	Operand label2 = op_var(VARIABLE, NORMAL, newVar(TYPE_LABEL));
	Operand label3 = NULL;
	translate_Cond(root->children[2], label1, label2);
	insert_code(singleOp(LABEL_, label1));
	translate_Stmt(root->children[4]);
	bool Else = root->children_num == 7;
	if(Else) {
		label3 = op_var(VARIABLE, NORMAL, newVar(TYPE_LABEL));
		insert_code(singleOp(GOTO_, label3));
	}
	insert_code(singleOp(LABEL_, label2));
	if(Else) {
		translate_Stmt(root->children[6]);
		insert_code(singleOp(LABEL_, label3));
	}
}

void translate_Stmt(struct TreeNode *root) {
	// Exp SEMI
	if(strcmp(root->children[0]->name, "Exp") == 0) translate_Exp(root->children[0], NULL);
	// CompSt
	else if(strcmp(root->children[0]->name, "CompSt") == 0) translate_CompSt(root->children[0]);
	// RETURN Exp SEMI
	else if(strcmp(root->children[0]->name, "RETURN") == 0) translate_Return(root);
	// WHILE LP Exp RP Stmt1
	else if(strcmp(root->children[0]->name, "WHILE") == 0) translate_While(root);
	// IF LP Exp RP Stmt1 || IF LP Exp RP Stmt1 ELSE Stmt 2
	else translate_If(root);
}

void translate_DefList(struct TreeNode *root) {
	// DefList → Def DefList 
	while(root->children_num == 2){
		/*Def → Specifier DecList SEMI*/
		struct TreeNode *DecList = root->children[0]->children[1];
		while(1) {
			// DecList → Dec | Dec COMMA DecList
			struct TreeNode *Dec = DecList->children[0];
			//Dec → VarDec | VarDec ASSIGNOP Exp
			struct TreeNode *VarDec = Dec->children[0];
		
			struct TreeNode* vdec;
			// VarDec → ID | VarDec LB INT RB
			while(vdec->children_num != 1){
				vdec = vdec->children[0];
			}
			char *id = vdec->children[0]->val_str;
			FieldList var = query(id);
			if(var->type->kind == STRUCTURE) {
				printf("%s\n", "Can't translate: Code contains variables of structure type.");
				assert(0);
			}
			var->var = newVar(TYPE_VAR);
			if(var->type->kind == ARRAY) {	
				var->type->width = calculate_width(var->type);
				Operand decop = op_var(VARIABLE, NORMAL, var->var);
				insert_code(dec(decop, var->type->width));
			}
			//Dec → VarDec ASSIGNOP Exp
			if(Dec->children_num == 3){
				Operand op = Operand_(VARIABLE, NORMAL);
				op->u.str = var->var;
				translate_Exp(Dec->children[2], op);
			}
			// DecList → Dec | Dec COMMA DecList*/
			if(DecList->children_num == 1) break;
			DecList = DecList->children[2];
		}
		root = root->children[1];
	}
}

void translate_ExtDefList(struct TreeNode *root) {
	// ExtDefList → ExtDef ExtDefList
	// ExtDef → Specifier FunDec CompSt | Specifier FunDec SEMI
	struct TreeNode *ExtDef = NULL;
	struct TreeNode *funDec = NULL;
	FieldList func, par = NULL;
	while(root->children_num){
		ExtDef = root->children[0];
		if(strcmp(ExtDef->children[1]->name, "FunDec") == 0){
			funDec = ExtDef->children[1];
			func = query(funDec->children[0]->val_str);
			par = func->type->u.function.params;
			Operand func_op = op_var(FUNC, NORMAL, func->name);
			insert_code(singleOp(FUNC_, func_op));
			currentParams = NULL;
			while(par) {
				par->var = newVar(TYPE_VAR);
				par->type->width = calculate_width(par->type);
				insert_param(par->var);
				Operand op_param = op_var(VARIABLE, NORMAL, par->var);
				insert_code(singleOp(PARAM_, op_param));
				par = par->tail;
			}
			translate_CompSt(ExtDef->children[2]);
		}
		root = root->children[1];
	}	
}

void printcodes(InterCodes head, FILE *output){
	if(head != codes){
		write_code(head->code, output);
		printcodes(head->next, output);
	}
}

void translate(struct TreeNode *root, FILE *output) {
	codes = init_node();
	struct TreeNode *ExtDefList = root->children[0];
	translate_ExtDefList(ExtDefList);
	printcodes(codes->next, output);
}