#include "generation.h"

#define TYPE_VAR 1
#define TYPE_TEMP 2
#define TYPE_LABEL 3

//InterCodes codes;
InterCodes codes;
struct Param *currentParams;

/*char *newVar(int type)
{
	char prefix;
	static int varCount = 1, tempCount = 1, labelCount = 1;
	int no;
	switch((int)type)
	{
		case TYPE_VAR: prefix = 'v'; no = varCount++; break;
		case TYPE_TEMP: prefix = 't'; no = tempCount++; break;
		case TYPE_LABEL: prefix = 'L'; no = labelCount++; break;
	}
	char *buf = malloc(10);
	sprintf(buf, "%c%d%c", prefix, no, '\0');
	return buf;
}*/

char *newVar(int type){
	char inf;
	static int cntvar = 0, cnttemp = 0, cntlabel = 0;
	int n;
	switch((int)type)
	{
	case TYPE_VAR: 
        inf = 'v'; 
        n = ++cntvar; 
        break;
	case TYPE_TEMP: 
        inf = 't'; 
        n = ++cnttemp; 
        break;
	case TYPE_LABEL: 
        inf = 'L'; 
        n = ++cntlabel; 
        break;
    default:
        printf("No match case in func new.\n");
        break;
	}
	char *ret = malloc(10);
	sprintf(ret, "%c%d%c", inf, n, '\0');
	return ret;
}

void translateError(char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(EXIT_FAILURE);
}

/*#######################################################################################*/
Operand newOperand(enum OPERAND_KIND kind, enum TYPE type)
{
	Operand op = (Operand )malloc(sizeof(struct Operand_));
	memset(op, 0, sizeof(op));
	op->kind = kind;
	op->type = type;
	return op;
}

Operand constantOperand(int value)
{
	Operand op = newOperand(CONSTANT, NORMAL);
	op->u.constant = value;
	return op;
}

Operand varOperand(enum OPERAND_KIND kind, enum TYPE type, char *text)
{
	Operand op = newOperand(kind, type);
	op->u.text = text;
	return op;
}

Operand copy(Operand operand)
{
	Operand op = newOperand(operand->kind, operand->type);
	if(operand->kind == CONSTANT)
		op->u.constant = operand->u.constant;
	else
		op->u.text = operand->u.text;
	return op;
}

/*###################################################################################*/
InterCode newIR(enum INTER_CODE_KIND kind)
{
	InterCode c = (InterCode)malloc(sizeof(struct InterCode_));
	c->kind = kind;
	return c;
}

InterCode singleOpIR(enum INTER_CODE_KIND kind, Operand operand)
{
	InterCode c = newIR(kind);
	c->singleop.op = operand;
	return c;
}

InterCode decIR(Operand var, int size)
{
	InterCode c = newIR(DEC_);
	c->dec.var = var;
	c->dec.size = size;
	return c;
}

InterCode binOpIR(enum INTER_CODE_KIND kind, Operand dest, Operand src)
{
	InterCode c = newIR(kind);
	c->binop.dest = dest;
	c->binop.src = src;
	return c;	
}

InterCode triOpIR(enum INTER_CODE_KIND kind, Operand dest, Operand o1, Operand o2)
{
	InterCode c = newIR(kind);
	c->triop.dest = dest;
	c->triop.op1 = o1;
	c->triop.op2 = o2;
	return c;
}

InterCode condJumpIR(Operand op1, Operand op2, 
							Operand dst, char *relop)
{
	InterCode  c = newIR(IF_GOTO_); 
	c->if_goto.op1 = op1;
	c->if_goto.op2 = op2;
	c->if_goto.dest = dst;
	c->if_goto.relop = relop;
	return c;
}

/*####################################################################################*/
/*Create a empty Intermediate code linked list. Initially, It contains an unused 
  head TreeNode. Next and prev fields all point to itsellf
*/
InterCodes createIRTreeNode()
{
	InterCodes iclist = (InterCodes )malloc(sizeof(struct InterCodes_));
	iclist->icode =  NULL;
	iclist->next = iclist;
	iclist->prev = iclist;
	return iclist;
}

void insertIR(InterCodes head, InterCode InterCode_)
{
	InterCodes TreeNode = createIRTreeNode();
	TreeNode->icode = InterCode_;
	TreeNode->prev = codes->prev;
	TreeNode->next = codes;
	codes->prev->next = TreeNode;
	codes->prev = TreeNode;
}


/*########################################################################################*/
void writeOp(Operand op, FILE *out)
{
	if(op->kind == CONSTANT)
		fprintf(out, "#%d", op->u.constant);
	else
	{
		if(op->type == ADDRESS)
			fprintf(out, "&");
		else if(op->type == STAR)
			fprintf(out, "*");
		fprintf(out, "%s", op->u.text);
	}
}

void writeIR(InterCode  InterCode_, FILE *out)
{
	switch(InterCode_->kind)
	{
		case LABEL_: case FUNC_: case PARAM_:case RETURN_:
		case GOTO_: case ARG_: case READ_: case WRITE_:
			switch(InterCode_->kind)
			{
				case LABEL_: fprintf(out, "LABEL ");break;
				case FUNC_: fprintf(out, "FUNCTION "); break;
				case PARAM_: fprintf(out, "PARAM "); break;
				case RETURN_: fprintf(out, "RETURN "); break;
				case GOTO_: fprintf(out, "GOTO "); break;
				case ARG_: fprintf(out, "Arg_ "); break;
				case READ_: fprintf(out, "READ "); break;
				case WRITE_: fprintf(out, "WRITE "); break;
			}
			writeOp(InterCode_->singleop.op, out);
			if(InterCode_->kind == LABEL_ || InterCode_->kind == FUNC_)
				fprintf(out, " :");
			break;
		case DEC_: 
			fprintf(out, "DEC "); 
			writeOp(InterCode_->dec.var, out); 
			fprintf(out, " %d", InterCode_->dec.size); break;
		case ASSIGN_: case CALL_:
			writeOp(InterCode_->binop.dest, out); 
			fprintf(out, " := "); 
			if(InterCode_->kind == CALL_)
				fprintf(out, "CALL ");
			writeOp(InterCode_->binop.src, out);break;
		case ADD_: case MUL_: case SUB_: case DIV_: 
			writeOp(InterCode_->triop.dest, out); fprintf(out, " := "); 
			writeOp(InterCode_->triop.op1, out); 
			switch(InterCode_->kind)
			{
				case ADD_: fprintf(out, " + "); break;
				case SUB_: fprintf(out, " - "); break;
				case MUL_: fprintf(out, " * "); break;
				case DIV_: fprintf(out, " / "); break;
			}
			writeOp(InterCode_->triop.op2, out); break;
		case IF_GOTO_:
			fprintf(out, "IF ");
			writeOp(InterCode_->if_goto.op1, out);
			fprintf(out, " %s ", InterCode_->if_goto.relop);
			writeOp(InterCode_->if_goto.op2, out);
			fprintf(out, " GOTO ");
			writeOp(InterCode_->if_goto.dest, out);
		default: break;
	}
	fprintf(out, "\n");
}

void printIRList(InterCodes head, FILE *out)
{
	if(head == codes)
		return;
	writeIR(head->icode, out);
	printIRList(head->next, out);
}

/*##################################################################################*/
int calculate_width(Type t)
{
	if(t->kind == BASIC)
	{
		t->width = 4;
		return 4;
	}
	t->width=t->u.array.size * calculate_width(t->u.array.elem);
	return t->width;
}

/*###############################################################################*/

void translate_ExtDefList(struct TreeNode *root);

void translate(struct TreeNode *root, FILE *out) {
	codes = createIRTreeNode();
	struct TreeNode *ExtDefList = root->children[0];
	translate_ExtDefList(ExtDefList);
	printIRList(codes->next, out);
}


void insertParam(char *text)
{
	struct Param *param = (struct Param *)malloc(sizeof(struct Param));
	param->var = text;
	param->next = NULL;
	if(currentParams == NULL)
		currentParams = param;
	else
	{
		param->next = currentParams;
		currentParams = param;
	}
}

int isInCurrentParams(char *text)
{
	struct Param *p = currentParams;
	while(p)
	{
		if(strcmp(p->var, text) == 0)
			return 1;
		p = p->next;
	}
	return 0;
}

//void translate_CompSt(struct TreeNode *root);
void translate_ExtDefList(struct TreeNode *root)
{
	struct TreeNode *ExtDef = NULL;
	struct TreeNode *funDec = NULL;
	FieldList fun, params = NULL;
	while(root->children_num != 0)
	{
		ExtDef = root->children[0];
		if(strcmp(ExtDef->children[1]->name, "FunDec") == 0)
		{
			funDec = ExtDef->children[1];
			fun = query(funDec->children[0]->val_str);
			
			params = fun->type->u.function.params;
			Operand opfunc = varOperand(FUNC, NORMAL, fun->name);
			insertIR(codes, singleOpIR(FUNC_, opfunc));
			currentParams = NULL;
			while(params)
			{
				params->var = newVar(TYPE_VAR);
				params->type->width = calculate_width(params->type);
				insertParam(params->var);
				Operand opparam = varOperand(VARIABLE, NORMAL, params->var);
				insertIR(codes, singleOpIR(PARAM_, opparam));
				params = params->tail;
			}
			translate_CompSt(ExtDef->children[2]);
		}
		root = root->children[1];
	}	
}

//void translate_Stmt(struct TreeNode *root);
//void translate_DefList(struct TreeNode *root);
void translate_CompSt(struct TreeNode *root)
{
	translate_DefList(root->children[1]);
	struct TreeNode *StmtList = root->children[2];
	while(StmtList->children_num == 2)
	{
		struct TreeNode *Stmt = StmtList->children[0];
		translate_Stmt(Stmt);
		StmtList = StmtList->children[1];
	}
}

//void translate_Cond(struct TreeNode *root, Operand , Operand );
void translate_IF(struct TreeNode *root)
{
	Operand label1 = varOperand(VARIABLE, NORMAL, newVar(TYPE_LABEL)),
				   label2 = varOperand(VARIABLE, NORMAL, newVar(TYPE_LABEL)),
				   label3 = NULL;
	translate_Cond(root->children[2], label1, label2);
	insertIR(codes, singleOpIR(LABEL_, label1));
	translate_Stmt(root->children[4]);
	int hasElse = ((root->children_num == 7) ? 1: 0);
	if(hasElse)
	{
		label3 = varOperand(VARIABLE, NORMAL, newVar(TYPE_LABEL));
		insertIR(codes, singleOpIR(GOTO_, label3));
	}
	insertIR(codes, singleOpIR(LABEL_, label2));
	if(hasElse)
	{
		translate_Stmt(root->children[6]);
		insertIR(codes, singleOpIR(LABEL_, label3));
	}
}

void translate_WHILE(struct TreeNode *root)
{
	Operand label1 = varOperand(VARIABLE, NORMAL, newVar(TYPE_LABEL)),
				   label2 = varOperand(VARIABLE, NORMAL, newVar(TYPE_LABEL)),
				   label3 = varOperand(VARIABLE, NORMAL, newVar(TYPE_LABEL));
	insertIR(codes, singleOpIR(LABEL_, label1));
	translate_Cond(root->children[2], label2, label3);
	insertIR(codes, singleOpIR(LABEL_, label2));
	translate_Stmt(root->children[4]);
	insertIR(codes, singleOpIR(GOTO_, label1));
	insertIR(codes, singleOpIR(LABEL_, label3));
}

//void translate_Exp(struct TreeNode *root, Operand );
void translate_Stmt(struct TreeNode *root)
{
	if(strcmp(root->children[0]->name, "CompSt") == 0)
		translate_CompSt(root->children[0]);
	else if(strcmp(root->children[0]->name, "Exp") == 0)
		translate_Exp(root->children[0], NULL);
	else if(strcmp(root->children[0]->name, "RETURN") == 0)
	{
		Operand op = varOperand(VARIABLE, NORMAL, newVar(TYPE_TEMP));
		translate_Exp(root->children[1], op);
		insertIR(codes, singleOpIR(RETURN_, op));
	}
	else if(strcmp(root->children[0]->name, "WHILE") == 0)
		translate_WHILE(root);
	else
		translate_IF(root);
}

void translate_Cond(struct TreeNode *root, Operand trueLabel, Operand falseLabel)
{
	if(root->children_num == 3 && strcmp(root->children[1]->name, "RELOP") == 0)
	{
		Operand t1 = varOperand(VARIABLE, NORMAL, newVar(TYPE_TEMP)),
					   t2 = varOperand(VARIABLE, NORMAL, newVar(TYPE_TEMP));
		translate_Exp(root->children[0], t1);
		translate_Exp(root->children[2], t2);
		char *relop = root->children[1]->val_str;
		insertIR(codes, condJumpIR(t1, t2, trueLabel, relop));
		insertIR(codes, singleOpIR(GOTO_, falseLabel));	
	}
	else if(root->children_num == 2 && strcmp(root->children[0]->name, "NOT") == 0)
	{
		translate_Cond(root->children[1], falseLabel, trueLabel);
	}
	else if(root->children_num == 3 && strcmp(root->children[1]->name, "AND") == 0)
	{
		Operand label = varOperand(VARIABLE, NORMAL, newVar(TYPE_LABEL));
		translate_Cond(root->children[0], label, falseLabel);
		insertIR(codes, singleOpIR(LABEL_, label));
		translate_Cond(root->children[2], trueLabel, falseLabel);
	}
	else if(root->children_num == 3 && strcmp(root->children[1]->name, "OR") == 0)
	{
		Operand label = varOperand(VARIABLE, NORMAL, newVar(TYPE_LABEL));
		translate_Cond(root->children[0], trueLabel, label);
		insertIR(codes, singleOpIR(LABEL_, label));
		translate_Cond(root->children[2], trueLabel, falseLabel);
	}
	else
	{
		Operand t = varOperand(VARIABLE, NORMAL, newVar(TYPE_TEMP)),
					   zero = constantOperand(0);
		translate_Exp(root, t);
		insertIR(codes, condJumpIR(t, zero, trueLabel, "!="));
		insertIR(codes, singleOpIR(GOTO_, falseLabel));
	}
}

static char *findVarName(struct TreeNode *VarDec)
{
	while(VarDec->children_num != 1)
		VarDec = VarDec->children[0];
	return VarDec->children[0]->val_str;
}

void translate_DefList(struct TreeNode *root)
{
	while(root->children_num == 2)
	{
		struct TreeNode *DecList = root->children[0]->children[1];
		while(1)
		{
			struct TreeNode *Dec = DecList->children[0];
			struct TreeNode *VarDec = Dec->children[0];
			char *name = findVarName(VarDec);
			FieldList var = query(name);
			if(var->type->kind == STRUCTURE)
				translateError("Can't translate: Code contains variables of structure type.");
			var->var = newVar(TYPE_VAR);
			if(var->type->kind == ARRAY)
			{	
				var->type->width = calculate_width(var->type);
				Operand decop = varOperand(VARIABLE, NORMAL, var->var);
				insertIR(codes, decIR(decop, var->type->width));
			}
			if(Dec->children_num == 3)
			{
				Operand op = newOperand(VARIABLE, NORMAL);
				op->u.text = var->var;
				translate_Exp(Dec->children[2], op);
			}
			if(DecList->children_num == 1)
				break;
			DecList = DecList->children[2];
		}
		root = root->children[1];
	}
}

Type translate_Array(struct TreeNode *root, Operand place)
{
	static char *var[10];
	static int level = 0;
	Type ret = NULL;
	if(strcmp(root->children[0]->children[0]->name, "ID") == 0)
	{
		struct TreeNode *ID = root->children[0]->children[0];
		FieldList field = query(ID->val_str);
		var[level++] = field->var;
		place->u.text = newVar(TYPE_VAR);
		Operand op = NULL;
		if(strcmp(root->children[2]->children[0]->name, "INT") == 0)
		{
			int value = root->children[2]->children[0]->val_int * field->type->u.array.elem->width;
			op = constantOperand(value);
			insertIR(codes, binOpIR(ASSIGN_, copy(place), op));
		}
		else
		{
			op = varOperand(VARIABLE, NORMAL, newVar(TYPE_TEMP));
			translate_Exp(root->children[2], op);
			Operand width = constantOperand(field->type->u.array.elem->width);
			insertIR(codes, triOpIR(MUL_, copy(place), op, width));
		}
		ret = field->type->u.array.elem;
	}
	else
	{
		Operand base = newOperand(VARIABLE, NORMAL);
		Type type = translate_Array(root->children[0], base);
		place->u.text = newVar(TYPE_TEMP);

		Operand op = varOperand(VARIABLE, NORMAL, newVar(TYPE_TEMP)),
					   index = varOperand(VARIABLE, NORMAL, newVar(TYPE_TEMP)),
					   width = constantOperand(type->u.array.elem->width);
		translate_Exp(root->children[2], index);
		insertIR(codes, triOpIR(MUL_, op, index, width));
		insertIR(codes, triOpIR(ADD_, copy(place), base, op));
		ret = type->u.array.elem;
	}
	if(ret->kind == 1)
	{
		Operand dest = varOperand(VARIABLE, NORMAL, newVar(TYPE_TEMP)),
					   addr = varOperand(VARIABLE, ADDRESS, var[--level]);
		if(isInCurrentParams(addr->u.text))
			addr->type = NORMAL;
		insertIR(codes, triOpIR(ADD_, dest, addr, copy(place)));
		place->type = STAR;
		place->u.text = dest->u.text;
	}
	return ret;
}

void translate_Assignment(struct TreeNode *root, Operand place)
{
	Operand dest = NULL;
	if(root->children[0]->children_num == 1)
	{
		struct TreeNode *ID = root->children[0]->children[0];
		FieldList field = query(ID->val_str);
		dest = varOperand(VARIABLE, NORMAL, field->var);
	}
	else
	{
		dest = varOperand(VARIABLE, NORMAL, newVar(TYPE_TEMP));
		translate_Array(root->children[0], dest);
	}
	Operand src = varOperand(VARIABLE, NORMAL, newVar(TYPE_TEMP));
	translate_Exp(root->children[2], src);
	insertIR(codes, binOpIR(ASSIGN_, dest, src));
	if(place)
		insertIR(codes, binOpIR(ASSIGN_, place, dest));
}

int isConditionExp(struct TreeNode *root)
{
	char *cond[] = {"AND", "OR", "RELOP"};
	if(root->children_num == 2 && strcmp(root->children[0]->name, "NOT") == 0)
		return 1;
	if(root->children_num == 3)
		for(int i = 0; i < 3; i++)
			if(strcmp(cond[i], root->children[1]->name) == 0)
				return 1;
	return 0;
}

void translate_Arithmetic(struct TreeNode *root, Operand place)
{
	Operand t1 = varOperand(VARIABLE, NORMAL, newVar(TYPE_TEMP));
	Operand t2 = varOperand(VARIABLE, NORMAL, newVar(TYPE_TEMP));
	translate_Exp(root->children[0], t1);
	translate_Exp(root->children[2], t2);
	enum INTER_CODE_KIND type;
	char *name = root->children[1]->name;
	if(strcmp(name, "PLUS") == 0)
		type = ADD_;
	else if(strcmp(name, "MINUS") == 0)
		type = SUB_;
	else if(strcmp(name, "STAR") == 0)
		type = MUL_;
	else
		type = DIV_;
	insertIR(codes, triOpIR(type, place, t1, t2));
}

static Arg newArg(Operand var)
{
	Arg Arg_ = (Arg )malloc(sizeof(struct Arg_));
	Arg_->arg = var;
	Arg_->next = NULL;
	return Arg_;
}

Arg insertArg(Arg list, Operand operand)
{
	if(list == NULL)
		list = newArg(operand);
	else
	{
		Arg new = newArg(operand);
		new->next = list;
		list = new;
	}
	return list;
}

Arg translate_Args(struct TreeNode *root, Arg list)
{
	Operand t = varOperand(VARIABLE, NORMAL, newVar(TYPE_TEMP));
	translate_Exp(root->children[0], t);
	list = insertArg(list, t);
	if(root->children_num == 3)
		list = translate_Args(root->children[2], list);
	return list;
}

void translate_funCall(struct TreeNode *root, Operand place)
{
	char *funcName = root->children[0]->val_str;
	if(strcmp(funcName, "read") == 0)
		insertIR(codes, singleOpIR(READ_, place));
	else if(strcmp(funcName, "write") == 0)
	{
		Operand t = varOperand(VARIABLE, NORMAL, newVar(TYPE_TEMP));
		translate_Exp(root->children[2]->children[0], t);
		insertIR(codes, singleOpIR(WRITE_, t));
	}
	else
	{
		 if(root->children_num == 4)
		 {
			Arg args = NULL;
			args = translate_Args(root->children[2], args);
			while(args)
			{
				insertIR(codes, singleOpIR(ARG_, args->arg));
				args = args->next;
			}
		}
		Operand func = varOperand(FUNC, NORMAL, funcName);
		if(!place)
			place = varOperand(VARIABLE, NORMAL, newVar(TYPE_TEMP));
		insertIR(codes, binOpIR(CALL_, place, func));
	}
}

void translate_Exp(struct TreeNode *root, Operand place)
{
	if(root->children_num == 1)
	{
		if(place && strcmp(root->children[0]->name, "INT") == 0)
		{
			Operand src = constantOperand(root->children[0]->val_int);
			insertIR(codes, binOpIR(ASSIGN_, place, src));
		}
		else if(place)
		{
			FieldList field = query(root->children[0]->val_str);
			Operand src = varOperand(VARIABLE, NORMAL, field->var);
			if(field->type->kind == ARRAY && isInCurrentParams(field->var) == 0)
				src->type = ADDRESS;
			insertIR(codes, binOpIR(ASSIGN_, place, src));
		}
	}
	else if(isConditionExp(root))
	{
		Operand label1 = varOperand(VARIABLE, NORMAL, newVar(TYPE_LABEL)), 
					   label2 = varOperand(VARIABLE, NORMAL, newVar(TYPE_LABEL)),
					   zero = constantOperand(0),
					   one = constantOperand(1);
		insertIR(codes, binOpIR(ASSIGN_, place, zero));
		translate_Cond(root, label1, label2);
		insertIR(codes, singleOpIR(LABEL_, label1));
		insertIR(codes, binOpIR(ASSIGN_, place, one));
		insertIR(codes, singleOpIR(LABEL_, label2));
	}
	else if(strcmp(root->children[1]->name, "LP") == 0)
		translate_funCall(root, place);
	else if(root->children_num == 2)
	{
		Operand zero = constantOperand(0);
		Operand t = varOperand(VARIABLE, NORMAL, newVar(TYPE_TEMP));
		translate_Exp(root->children[1], t);
		insertIR(codes, triOpIR(SUB_, place, zero, t));	
	}
	else if(root->children_num == 3)
	{
		if(strcmp(root->children[1]->name, "ASSIGNOP") == 0)
			translate_Assignment(root, place);
		else if(strcmp(root->children[1]->name, "Exp") == 0)
			translate_Exp(root->children[1], place);
		else
			translate_Arithmetic(root, place);
	}
	else	
	{
		if(strcmp(root->children[0]->name, "Exp") == 0)
			translate_Array(root, place);	
	}
}