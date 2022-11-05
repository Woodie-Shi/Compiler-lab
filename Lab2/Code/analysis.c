#include "analysis.h"

FieldList hash_table[HASH];
char* func_table[FUNCTION];
static int isstructue = 0; 
static int func_num = 0;

unsigned int hash_pjw(char* name){
    unsigned int val = 0, i;
    for (; *name; ++name){
        val = (val << 2) + *name;
        if (i = val & ~0x3fff) val = (val ^ (i >> 12)) & 0x3fff;
        }
        return val;
}

void init_hash(){
    for(int i = 0;i < HASH;i++) hash_table[i] = NULL;
}

bool fill_in(FieldList f){
    if(f == NULL) return false;
    if(f->name == NULL) return false;
    unsigned int key = hash_pjw(f->name);
    for(int i = 0;i < HASH;i++){
        int entry = (i + key) % HASH;
        if(hash_table[entry] == NULL){
            hash_table[entry] = f;
            return true;
        }
    }
    return false;
}

FieldList query(char* name){
    if(name == NULL) return NULL;
    unsigned int key = hash_pjw(name);
    for(int i = 0;i < HASH;i++){
        int entry = (i + key) % HASH;
        if(hash_table[entry] == NULL || strcmp(hash_table[entry]->name, name) == 0) return hash_table[entry];
    }
    return NULL;
}

void show_symbol(){
	for(int i = 0;i < HASH;i++){
		if(hash_table[i]!=NULL){
            printf("name:%s\n",hash_table[i]->name);
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

Type get_type_one(TreeNode* root){
    Type type=(Type)malloc(sizeof(struct Type_));
    //INT
    if(strcmp(root->children[0]->name,"INT") == 0){
        type->kind=BASIC;
        type->u.basic = 1;
    }
    //FLOAT
    else if(strcmp(root->children[0]->name,"FLOAT") == 0){
        type->kind=BASIC;
        type->u.basic= 2;
    }
    //ID
    else if(strcmp(root->children[0]->name,"ID") == 0){
        //bug: FieldList f = quiery(root->children[0]->name);
        FieldList f = query(root->children[0]->val_str);
        if(f) type = f->type;
        else{
            printf("Error type 1 at Line %d: Undefined variable \"%s\".\n", root->lineno,root->children[0]->val_str);
            return NULL;
        }
    }
    return type;
}

Type get_type_structure(TreeNode* root){
	Type temp = Exp(root->children[0]);
    if(temp){
        if(temp->kind != STRUCTURE){
            printf("Error type 13 at Line %d: Illegal use of \".\".\n", root->lineno);
            return NULL;
        }
        else{
            FieldList f = temp->u.structure.structfield;
            while(f){
                if(strcmp(f->name, root->children[2]->val_str) == 0) return f->type;
                f = f->tail;
            }
            printf("Error type 14 at Line %d: Non-existent field \"%s\".\n", root->lineno,  root->children[2]->val_str);
        }
    }
    else assert(0);
	return NULL;
}

Type get_type_array(TreeNode* root){
	Type temp = Exp(root->children[0]);
	if(Exp(root->children[2])->u.basic != 1) printf("Error type 12 at Line %d: \"%g\" is not an integer.\n", root->lineno, root->children[2]->children[0]->val_float);
	if(temp){
        TreeNode* tmp = root->children[0];
        char *s;
        switch(tmp->children_num){
            case 1:
                if(strcmp(tmp->children[0]->name, "ID") == 0) s = tmp->children[0]->val_str;
                break;
            case 3:
                if(strcmp(tmp->children[2]->name, "ID") == 0) s = tmp->children[0]->val_str;
                break;
            case 4:
                if(strcmp(tmp->children[0]->name,"Exp") == 0){
                    if(strcmp(tmp->children[0]->children[0]->name,"ID") == 0) s = tmp->children[0]->children[0]->val_str;
                }
                break;
            default:
                s = ""; 
                break;
        }
        if(temp->kind != ARRAY) printf("Error type 10 at Line %d: \"%s\" is not an array.\n", root->lineno, s);
        else return temp->u.array.elem;
    }
    else assert(0);
	return NULL;
}

void merge_field(FieldList* l1, FieldList l2){
    if(!*l1) *l1 = l2;
	else{
		FieldList p = *l1;
		while(p->tail) p = p->tail;
		p->tail = l2;
	}
}

bool check_equivalent(Type x, Type y){
    if(!x || !y) return false;
    if(x->kind != y->kind) return false;
    switch(x->kind){
    case BASIC :
        if(x->u.basic == y->u.basic) return true;
        else return false;
        break;
    case ARRAY :
        if(check_equivalent(x->u.array.elem, y->u.array.elem)) return true;
        else return false;
        break;
    case STRUCTURE :
        FieldList f1 = x->u.structure.structfield;
        FieldList f2 = y->u.structure.structfield;
        if(f1 && f2){
            while(f1 && f2){
                if(!check_equivalent(f1->type, f2->type)) return false;
                f1 = f1->tail;
                f2=f2->tail;
            }
            if(!f1 && !f2) return true;
        }
        return false;
        break;
    default :
        if(x->u.function.returnVal && y->u.function.returnVal){
            if(!check_equivalent(x->u.function.returnVal, y->u.function.returnVal)) return false;
            FieldList f1 = x->u.function.params;
            FieldList f2 = y->u.function.params;
            while(f1 && f2){
                if(!check_equivalent(f1->type, f2->type)) return false;
                f1 = f1->tail;
                f2 = f2->tail;
            }
            if(!f1 && !f2) return true;
        }
        break;
    }
    return false;
}

Type get_type_func(TreeNode* root){
	FieldList f = query(root->children[0]->val_str);
	if(!f) printf("Error type 2 at Line %d: Undefined function \"%s\".\n", root->lineno, root->children[0]->val_str);
    else{
        if(f->type->kind != FUNCTION) printf("Error type 11 at Line %d: \"%s\" is not a function.\n", root->lineno, root->children[0]->val_str);
        else{
            TreeNode* params = NULL;
		    if(root->children_num == 4) params = root->children[2];
		    Type type = (Type)malloc(sizeof(struct Type_));
		    type->kind = FUNCTION;
            type->u.function.returnVal = f->type->u.function.returnVal;
            if(root->children_num == 4){
                while(1){
                    FieldList l = (FieldList)malloc(sizeof(struct FieldList_));
			        l->type = Exp(params->children[0]);
                    merge_field(&type->u.function.params, l);
			        if(params->children_num == 1) break;
                    params = params->children[2];
                }
            }
		    if(!check_equivalent(type, f->type)){
                //printf("Error type 9 at Line %d: Function \"%s\" is not applicable for arguments (a ,b).\n", root->lineno, root->val_str);
                printf("Error type 9 at Line %d: Function \"%s(", root->lineno, root->children[0]->val_str);
                FieldList temp = f;
                FieldList tmp = type->u.function.params;
                while(temp){
                    if(temp->type->kind == 0){
                        if(temp->type->u.basic == 1) printf("int");
                        else printf("float");
                    }
                    if(temp->tail) printf(", ");
                    temp = temp->tail;
                }
                printf(")\" is not applicable for arguments \"(\n");
                while(tmp){
                    if(tmp->type->kind == 0){
                        if(tmp->type->u.basic == 1) printf("int");
                        else printf("float");
                    }
                    if(tmp->tail) printf(", ");
                    tmp = tmp->tail;
                }
                printf(")\".\n");
            }

            return f->type->u.function.returnVal;
	    }
        return NULL;
    }
}

Type get_type_assignop(TreeNode* root){
    if(root->children[0]->children_num == 1){
        if(strcmp(root->children[0]->children[0]->name,"ID")){
            printf("Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n",root->lineno);
            return NULL;
        }
    }
    else if(root->children[0]->children_num == 3){
        if(!((strcmp(root->children[0]->children[0]->name,"Exp") == 0)
        &&(strcmp(root->children[0]->children[1]->name,"DOT") == 0)
        &&(strcmp(root->children[0]->children[2]->name,"ID") == 0))){
        printf("Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n",root->lineno);
        return NULL;
        }
    }
    else if(root->children[0]->children_num == 4){
        if(!((strcmp(root->children[0]->children[0]->name,"Exp") == 0)
        &&(strcmp(root->children[0]->children[1]->name,"LB") == 0)
        &&(strcmp(root->children[0]->children[2]->name,"Exp") == 0)
        &&(strcmp(root->children[0]->children[3]->name,"RB") == 0))){
            printf("Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n",root->lineno);
            return NULL;
        }
    }
    Type t1=Exp(root->children[0]);
    Type t2=Exp(root->children[2]);
    if(!check_equivalent(t1, t2)){
        if(t1 && t2){
            printf("Error type 5 at Line %d: Type mismatched for assignment.\n",root->lineno);
            return NULL;
        }
    }
    else return t1;
}

Type get_type_arithmetic(TreeNode* root){
    Type t1=Exp(root->children[0]);
    Type t2=Exp(root->children[2]);
    if(!check_equivalent(t1, t2)){
        if(t1 && t2) printf("Error type 7 at Line %d: Type mismatched for operands.\n",root->lineno);
        return NULL;
    }
    return t1;
}

Type get_type_logic(TreeNode* root){
    Type t1=Exp(root->children[0]);
    Type t2=Exp(root->children[2]);
    if(!check_equivalent(t1,t2)){
        if(t1 && t2) printf("Error type 7 at Line %d: Type mismatched for operands.\n",root->lineno);
        return NULL;
    }
    else{
	    Type t=(Type)malloc(sizeof(struct Type_));
        t->kind = BASIC;
	    t->u.basic = 1;
  	    return t;
	}
    return NULL;
}

Type Exp(TreeNode* root){
    if(!root) return NULL;
    // INT || FLOAT || ID
    if(root->children_num == 1) return get_type_one(root);
    // Exp DOT ID
    else if(strcmp(root->children[1]->name, "DOT") == 0) return get_type_structure(root);
    // Exp LB Exp RB
    else if(root->children_num == 4 && strcmp(root->children[1]->name, "LB") == 0 && strcmp(root->children[3]->name, "RB") == 0){
        return get_type_array(root);
    }
    // ID LP Args RP | ID LP RP
    else if(strcmp(root->children[0]->name, "ID") == 0 && strcmp(root->children[1]->name, "LP") == 0){
        return get_type_func(root);
    }
    // Exp ASSIGNOP Exp
    else if(strcmp(root->children[1]->name, "ASSIGNOP") == 0) return get_type_assignop(root);
    // LP Exp RP | MINUS Exp | NOT Exp
    else if((strcmp(root->children[0]->name, "LP") == 0)
    ||(strcmp(root->children[0]->name, "MINUS") == 0)
    ||(strcmp(root->children[0]->name, "NOT") == 0)){
        return Exp(root->children[1]);
    }
    // Exp PLUS Exp | Exp MINUS Exp | Exp STAR Exp | Exp DIV Exp
    else if((strcmp(root->children[1]->name, "PLUS") == 0)
    ||(strcmp(root->children[1]->name, "MINUS") == 0)
    ||(strcmp(root->children[1]->name, "STAR") == 0)
    ||(strcmp(root->children[1]->name, "DIV") == 0)){
        return get_type_arithmetic(root);
    }
    // Exp AND Exp | Exp OR Exp | Exp RELOP Exp
    else if((strcmp(root->children[1]->name, "AND") == 0)
    ||(strcmp(root->children[1]->name, "OR") == 0)
    ||(strcmp(root->children[1]->name, "RELOP") == 0)){
        get_type_logic(root);
    }
    return NULL;
}

/*Stmt → Exp SEMI
| CompSt
| RETURN Exp SEMI
| IF LP Exp RP Stmt
| IF LP Exp RP Stmt ELSE Stmt
| WHILE LP Exp RP Stmt*/
void Stmt(TreeNode* root, Type function){
    // CompSt
    if(root->children_num == 1) CompSt(root->children[0], function);
    // Exp SEMI
	else if(root->children_num == 2) Exp(root->children[0]);
    // RETURN Exp SEMI
	else if(root->children_num == 3)
	{
        Type returnType = Exp(root->children[1]);
        Type funcType = function->u.function.returnVal;
        if(!check_equivalent(funcType, returnType)) printf("Error type 8 at Line %d: Type mismatched for return.\n", root->lineno);
	}
    // WHILE LP Exp RP Stmt
    else if(strcmp(root->children[0]->name, "WHILE")==0){
        Type t=Exp(root->children[2]);
        /*if(!((t->kind==BASIC)&&(t->u.basic = 1))){
            printf("Error type  at Line %d: Only type INT could be used for judgement.\n", root->lineno);
        }*/
        Stmt(root->children[4], function);
    }
    // IF LP Exp RP Stmt | IF LP Exp RP Stmt ELSE Stmt
	else if(strcmp(root->children[0]->name,  "IF") == 0)
	{
		Exp(root->children[2]);			
		Stmt(root->children[4], function);
		if(root->children_num == 7) Stmt(root->children[6],function);	
	}
}

void fill_in_list(FieldList flist){
	FieldList f = flist;
	while(f)
	{
        //check Error type 15: Duplicate definition of domain name in structure
		int error15 = 0; 
		if(isstructue)
		{
			FieldList pre = flist;
            //for each field in FieldList, compare all other fields before it.
			while(pre != f){
				if(strcmp(pre->name, f->name) == 0){
                    error15++;
					printf("Error type 15 at Line %d: Redefined field \"%s\".\n", f->lineno, f->name);
					break;
				}
				pre = pre->tail;
			}		
		}
		if(!error15){
            //check if collison
			if(query(f->name)) printf("Error type 3 at Line %d: Redefined variable \"%s\".\n", f->lineno, f->name);
			else fill_in(f);
		}
		f = f->tail;
	}	
}

/*CompSt → LC DefList StmtList RC
StmtList → Stmt StmtList*/
void CompSt(TreeNode* root, Type function){
    DefList(root->children[1]);
    TreeNode *StmtList = root->children[2];
    while(StmtList->children_num == 2){
        TreeNode *stmt=StmtList->children[0];
        Stmt(stmt,function);
        StmtList=StmtList->children[1];
    }
}

/*FunDec → ID LP VarList RP
| ID LP RP*/
Type FunDec(TreeNode* root, Type return_type, bool flag){
    FieldList params = NULL;
    //ID LP VarList RP
	if(root->children_num == 4){
		TreeNode* VarList = root->children[2];
		while(1){
            /*VarList → ParamDec COMMA VarList
            | ParamDec*/
			TreeNode* ParamDec = VarList->children[0];	
			Type t = Specifier(ParamDec->children[0]);
			FieldList param = VarDec(ParamDec->children[1], t);
			merge_field(&params, param);
			if(VarList->children_num == 1) break;
			VarList = VarList->children[2];
		}
	}
	if(flag) fill_in_list(params);
    Type type = (Type)malloc(sizeof(struct Type_));
	type->kind = FUNCTION;
	type->u.function.params = params;
	type->u.function.returnVal = return_type;
    type->u.function.status = (flag == 1) ? DEFINED : DECLARED;

    FieldList f = query(root->children[0]->val_str);
    if(f){
        if(flag && f->type->u.function.status){
            printf("Error type 4 at Line %d: Redefined function \"%s\".\n", root->lineno, f->name);
        }
        else{
            if(!check_equivalent(type, f->type)){
                if(type->u.function.status != f->type->u.function.status){
                    printf("Error type 18 at Line %d: Undefined function \"%s\".\n", f->lineno, f->name);
                }
                else{
                    printf("Error type 19 at Line %d: Inconsistent declaration of function \"%s\".\n", root->lineno, f->name);
                }
            }
            if(flag) f->type->u.function.status = 1;
            else f->type->u.function.status = 0;
        }
    }
    else{
        f = (FieldList)malloc(sizeof(struct FieldList_));		
		f->lineno = root->lineno;
		f->name = root->children[0]->val_str;
		f->type = type;
		bool success = fill_in(f);
        func_table[func_num++] = f->name;
		assert(success);
    }
	return type;
}

/*VarDec → ID
| VarDec LB INT RB*/
FieldList VarDec(TreeNode* root, Type type){
    FieldList f = (FieldList)malloc(sizeof(struct FieldList_));
	f->lineno = root->lineno;
    // VarDec → ID
	if(root->children_num == 1){
		f->name = root->children[0]->val_str;
		f->tail = NULL;
		f->type = type;
	}
    // VarDec LB INT RB
	else if(strcmp(root->children[1]->name, "LB") == 0){
		TreeNode* VarDec = root;
		Type t = NULL;
		while(VarDec->children_num == 4){
			Type temp = (Type)malloc(sizeof(struct Type_));
			temp->kind = ARRAY;
            temp->u.array.size = VarDec->children[2]->val_int;
			if(!t){
				t = temp;
				t->u.array.elem = type;
			}
			else{
				temp->u.array.elem = t;
				t = temp;
			}
			VarDec = VarDec->children[0];
			if(VarDec->children_num == 1) f->name = VarDec->children[0]->val_str;
		}
		f->type = t;
	}
	return f;
}

/*DefList → Def DefList
|  epsilon*/
FieldList DefList(TreeNode* root){
    FieldList deflist = NULL;
	while(root && root->children_num == 2){
		TreeNode* Def = root->children[0];
        /*Def → Specifier DecList SEMI*/
        TreeNode* DecList = Def->children[1];
		Type type = Specifier(Def->children[0]);
		while(1){
            /*DecList → Dec | Dec COMMA DecList*/
			TreeNode* Dec = DecList->children[0];
            /*Dec → VarDec*/		
			TreeNode* Vardec = Dec->children[0];
			FieldList f = VarDec(Vardec, type);
            if(!isstructue){
                if(Dec->children_num == 3){
                    Type x = f->type;
					Type y = Exp(Dec->children[2]);
					if(x && y && !check_equivalent(x, y)) printf("Error type 5 at Line %d: Type mismatched for assignment.\n", Vardec->lineno);
                }
                if(query(f->name)){
					printf("Error type 3 at Line %d: Redefined variable \"%s\".\n", Vardec->lineno, f->name);
                }
				else fill_in(f);
            }
            merge_field(&deflist, f);
			if(DecList->children_num == 1) break;
			DecList = DecList->children[2];
        }
        root = root->children[1];
    }
    return deflist;
}

/*Specifier → TYPE
    | StructSpecifier

    StructSpecifier → STRUCT OptTag LC DefList RC
    | STRUCT Tag    

    OptTag → ID
    | epsilon

    Tag → ID*/
Type Specifier(TreeNode* root){
    Type type = (Type )malloc(sizeof(struct Type_));
    /*Specifier → TYPE  | StructSpecifier*/
	if(strcmp(root->children[0]->name, "TYPE") == 0){
		type->kind = BASIC;
        type->u.basic = 1;
        if(strcmp(root->children[0]->val_str, "float") == 0) type->u.basic = 2;
	}
	else{ 
		type->kind = STRUCTURE;
		TreeNode* StructSpecifier = root->children[0];
        /*StructSpecifier → STRUCT OptTag LC DefList RC | STRUCT Tag*/
        if(StructSpecifier->children_num == 2){
            /*Tag → ID*/
            char *id = StructSpecifier->children[1]->children[0]->val_str;
			FieldList f = query(id);
			if(f) type = f->type;
            else{
				printf("Error type 17 at Line %d: Undefined structure \"%s\".\n", StructSpecifier->lineno, id);
				return NULL;
			}
        }
		else{
			TreeNode* deflist = StructSpecifier->children[3];
			isstructue++;
			FieldList f = DefList(deflist);
			fill_in_list(f);
			isstructue--;
            type->u.structure.structfield = f;
            /*OptTag → ID
                | epsilon */
			if(StructSpecifier->children[1]->children_num){
				FieldList s = (FieldList)malloc(sizeof(struct FieldList_));
				s->name = StructSpecifier->children[1]->children[0]->val_str;
                s->lineno = StructSpecifier->lineno;
                type->u.structure.id = s->name;
				s->type = type;
				if(query(s->name)){
					printf("Error type 16 at line %d: Duplicated name \"%s\".\n", StructSpecifier->lineno, s->name);
                }
                else fill_in(s);
			}
		}
	}
	return type;
}

/*ExtDefList → ExtDef ExtDefList
    | epsilon

    ExtDef → Specifier ExtDecList SEMI
    | Specifier SEMI
    | Specifier FunDec CompSt
    (*)
    | Specifier FunDec SEMI

    ExtDecList → VarDec
    | VarDec COMMA ExtDecList*/
void ExtDefList(TreeNode* root){
    TreeNode *ExtDefList = root;
	while(ExtDefList->children_num == 2){
		TreeNode *ExtDef = ExtDefList->children[0];
		Type type = Specifier(ExtDef->children[0]);
        /*ExtDef → Specifier FunDec CompSt
                                Specifier FunDec SEMI
        */
		if(strcmp(ExtDef->children[1]->name, "FunDec") == 0){
			bool flag = (strcmp(ExtDef->children[2]->name, "CompSt") == 0);
			Type t = FunDec(ExtDef->children[1], type, flag);
			if(flag) CompSt(ExtDef->children[2], t);
		}
        
        // ExtDef → Specifier ExtDecList SEMI
		else if(strcmp(ExtDef->children[1]->name, "ExtDecList") == 0){
			TreeNode* ExtDecList = ExtDef->children[1];
			while(1){
				TreeNode* Vardec = ExtDecList->children[0];
				FieldList f = VarDec(Vardec, type);
				if(query(f->name)){
					printf("Error type 3 at Line %d: Redefined variable \"%s\".\n",Vardec->lineno, f->name);
                }
				else fill_in(f);
				if(ExtDecList->children_num == 1) break;
				ExtDecList = ExtDecList->children[2];
			}
		}
		ExtDefList = ExtDefList->children[1];
	}	
}

/*Program → ExtDefList*/
void Program(TreeNode* root){
    ExtDefList(root->children[0]);
	for(int i = 0; i < func_num; i++)
	{
		FieldList f = query(func_table[i]);	
		if(!f->type->u.function.status) printf("Error type 18 at Line %d: Undefined function \"%s\".\n",f->lineno,  func_table[i]);
	}
}