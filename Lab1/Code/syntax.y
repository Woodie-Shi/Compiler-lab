%{
    #include <stdio.h>
    #include <stdlib.h>
    #include<string.h>
    #include "syntaxTree.h"
    #include "lex.yy.c"
    int Error = 0;
    extern int yylineno;
    extern TreeNode* treeRoot;
    void yyerror(char *msg);
    void print_error(char* msg);
%}

%locations

%union  {
    TreeNode* treeNode;
}

//terminal token
//%token <type_int> INT
//%token <type_float> FLOAT
//%token <type_str> ID SEMI COMMA ASSIGNOP RELOP
//%token <type_str> PLUS MINUS STAR DIV 
//%token <type_str> AND OR DOT NOT LP RP LB RB LC RC
//%token <type_str> STRUCT RETURN IF ELSE WHILE
%token <treeNode> INT FLOAT 
%token <treeNode> ID SEMI COMMA ASSIGNOP RELOP
%token <treeNode> PLUS MINUS STAR DIV 
%token <treeNode> AND OR NOT DOT
%token <treeNode> TYPE
%token <treeNode> LP RP LB RB LC RC
%token <treeNode> STRUCT RETURN IF ELSE WHILE

//non-terminal type
//%type <type_str> Program ExtDefList ExtDef ExtDecList Specifier
//%type <type_str> StructSpecifier OptTag Tag VarDec FunDec VarList
//%type <type_str> ParamDec CompSt StmtList Stmt DefList Def DecList
//%type <type_str> Dec Exp Args
%type <treeNode> Program ExtDefList ExtDef ExtDecList Specifier
%type <treeNode> StructSpecifier OptTag Tag VarDec FunDec VarList
%type <treeNode> ParamDec CompSt StmtList Stmt DefList Def DecList
%type <treeNode> Dec Exp Args

//association
%right ASSIGNOP  
%left OR 
%left AND 
%left RELOP
%left PLUS MINUS 
%left STAR DIV
%right NOT
%left LB RB LP RP DOT

//noassociation
%nonassoc LOWER_THAN_ELSE 
%nonassoc ELSE

%%
//High-level Definitions
Program : ExtDefList{
treeRoot = node_init("Program", syntactic);
TreeNode* children[] = {$1};
node_insert(1, treeRoot, children);
}
    ;
ExtDefList : ExtDef ExtDefList{
    $$ = node_init("ExtDefList", syntactic);
    TreeNode* children[] = {$1, $2};
    node_insert(2, $$, children);
}
    |  {/* empty*/
    $$ = node_init("ExtDecList", syntactic);
}
    ;     
ExtDef : Specifier ExtDecList SEMI{
    $$ = node_init("ExtDef", syntactic);
    TreeNode* children[] = {$1, $2, $3};
    node_insert(3, $$, children);
}
    | Specifier SEMI{
        $$ = node_init("ExtDef", syntactic);
        TreeNode* children[] = {$1, $2};
        node_insert(2, $$, children);
    }
    | Specifier FunDec CompSt{
        $$ = node_init("ExtDef", syntactic);
        TreeNode* children[] = {$1, $2, $3};
        node_insert(3, $$, children);
    }
    ;
ExtDecList : VarDec{
    $$ = node_init("ExtDecList", syntactic);
    TreeNode *children[] = {$1};
    node_insert(1, $$, children);
}
    | VarDec COMMA ExtDecList{
        $$ = node_init("ExtDecList", syntactic);
	    TreeNode *children[] = {$1, $2, $3};
		node_insert(3, $$, children);
    }
    | VarDec error ExtDecList{    
        Error++;
        print_error("Missing \",\".");
        }
    ;

//Specifiers
Specifier : TYPE{
    $$ = node_init("Specifier", syntactic);
	TreeNode *children[] = {$1};
	node_insert(1, $$, children);
}
    | StructSpecifier{
        $$ = node_init("Specifier", syntactic);
		TreeNode *children[] = {$1};
		node_insert(1, $$, children);		
    }
    ;   
StructSpecifier : STRUCT OptTag LC DefList RC{
    $$ = node_init("StructSpecifier", syntactic);
	TreeNode *children[] = {$1, $2, $3, $4, $5};
	node_insert(5, $$, children);
}
    | STRUCT Tag{
        $$ = node_init("StructSpecifier", syntactic);
		TreeNode *children[] = {$1, $2};
		node_insert(2, $$, children);
    }
    ;
OptTag : ID{
    $$ = node_init("OptTag", syntactic);
	TreeNode *children[] = {$1};
	node_insert(1, $$, children);
}
    | {/* empty*/
        $$ = node_init("OptTag", syntactic);
    }
    ;
Tag : ID{
    $$ = node_init("Tag", syntactic);
	TreeNode *children[] = {$1};
	node_insert(1, $$, children);
}
    ;

//Declarators
VarDec : ID{
    $$ = node_init("VarDec", syntactic);
	TreeNode *children[] = {$1};
	node_insert(1, $$, children);
}
    | VarDec LB INT RB{
        $$ = node_init("VarDec", syntactic);
		TreeNode *children[] = {$1, $2, $3, $4};
		node_insert(4, $$, children);
    }
    | VarDec LB error{
        Error++;
        print_error("Missing \"]\".");
        }
    ;
FunDec : ID LP VarList RP{
    $$ = node_init("FunDec", syntactic);
	TreeNode *children[] = {$1, $2, $3, $4};
	node_insert(4, $$, children);
}
    | ID LP RP{
        $$ = node_init("FunDec", syntactic);
		TreeNode *children[] = {$1, $2, $3};
		node_insert(3, $$, children);
    }
    | error LP VarList RP  {
        Error++;
        print_error("Missing function name."); 
        }
    ;
VarList : ParamDec COMMA VarList{
    $$ = node_init("VarList", syntactic);
	TreeNode* children[] = {$1, $2, $3};
	node_insert(3, $$, children);
}
    | ParamDec{
        $$ = node_init("VarList", syntactic);
		TreeNode* children[] = {$1};
        node_insert(1, $$, children);
    }
    ;          
ParamDec : Specifier VarDec{
    $$ = node_init("ParamDec", syntactic);
	TreeNode *children[] = {$1, $2};
	node_insert(2, $$, children);
}
    | error COMMA{
        Error++;
        print_error("Missing \";\".");
    }
    | error RP{
        Error++;
        print_error("Missing \")\".");
    }
    ;

//Statements
CompSt : LC DefList StmtList RC{
    $$ = node_init("CompSt", syntactic);
	TreeNode* children[] = {$1, $2, $3, $4};
	node_insert(4, $$, children);
}
    ;  
StmtList : Stmt StmtList{
    $$ = node_init("StmtList", syntactic);
	TreeNode *children[] = {$1, $2};
	node_insert(2, $$, children);
}
    | {/*empty*/
        $$ = node_init("StmtList", syntactic);
    }
    ;
Stmt : Exp SEMI{
    $$ = node_init("Stmt", syntactic);
	TreeNode* children[] = {$1, $2};
	node_insert(2, $$, children);
}
    | CompSt{
        $$ = node_init("Stmt", syntactic);
		TreeNode* children[] = {$1};
		node_insert(1, $$, children);
    }
    | RETURN Exp SEMI{
        $$ = node_init("Stmt", syntactic);
		TreeNode* children[] = {$1, $2, $3};
		node_insert(3, $$, children);
    }
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE{
        $$ = node_init("Stmt", syntactic);
	    TreeNode* children[] = {$1, $2, $3, $4, $5};
		node_insert(5, $$, children);
    }
    | IF LP Exp RP Stmt ELSE Stmt{
        $$ = node_init("Stmt", syntactic);
		TreeNode* children[] = {$1, $2, $3, $4, $5, $6, $7};
		node_insert(7, $$, children);
    }
    | WHILE LP Exp RP Stmt{
        $$ = node_init("Stmt", syntactic);
		TreeNode* children[] = {$1, $2, $3, $4, $5};
		node_insert(5, $$, children);
    }
    | Exp error{
        Error++;
        print_error("Missing \";\".");
    }
    | error SEMI{
        Error++;
        print_error("Error statements.");
        }
    | RETURN Exp error{
        Error++;
        print_error("Missing \";\".");
    }
    | WHILE error RP{
        Error++;
        print_error("Missing \"(\".");
    }
    | WHILE error RC{
        Error++;
        print_error("Missing \"{\".");
    }
    ;

//Local Definitions
DefList : Def DefList{
    $$ = node_init("DefList", syntactic);
	TreeNode* children[] = {$1, $2};
	node_insert(2, $$, children);
}
    | {/*empty*/
        $$ = node_init("DefList", syntactic);
    }
    ;    
Def : Specifier DecList SEMI{
    $$ = node_init("Def", syntactic);
	TreeNode* children[] = {$1, $2, $3};
	node_insert(3, $$, children);
}
    ;
DecList : Dec{
    $$ = node_init("DecList", syntactic);
	TreeNode* children[] = {$1};
	node_insert(1, $$, children);
}
    | Dec COMMA DecList{
        $$ = node_init("DecList", syntactic);
		TreeNode* children[] = {$1, $2, $3};
		node_insert(3, $$, children);
    }
    | Dec error DecList {
        Error++;
        print_error("Missing \",\".");
        }
    ;
Dec : VarDec{
    $$ = node_init("Dec", syntactic);
	TreeNode* children[] = {$1};
	node_insert(1, $$, children);
}
    | VarDec ASSIGNOP Exp{
        $$ = node_init("Dec", syntactic);
		TreeNode* children[] = {$1, $2, $3};
		node_insert(3, $$, children);
    }
    | VarDec ASSIGNOP error SEMI{
        Error++;
        print_error("Error expression");
    }
    ;
                
//Expressions
Exp : Exp ASSIGNOP Exp{
    $$ = node_init("Exp", syntactic);
	TreeNode* children[] = {$1, $2, $3};
	node_insert(3, $$, children);
}
    | Exp AND Exp{
        $$ = node_init("Exp", syntactic);
	    TreeNode* children[] = {$1, $2, $3};
	    node_insert(3, $$, children);
    }
    | Exp OR Exp{
        $$ = node_init("Exp", syntactic);
	    TreeNode* children[] = {$1, $2, $3};
	    node_insert(3, $$, children);
    }
    | Exp RELOP Exp{
        $$ = node_init("Exp", syntactic);
	    TreeNode* children[] = {$1, $2, $3};
	    node_insert(3, $$, children);
    }
    | Exp PLUS Exp{
        $$ = node_init("Exp", syntactic);
	    TreeNode* children[] = {$1, $2, $3};
	    node_insert(3, $$, children);
    }
    | Exp MINUS Exp{
        $$ = node_init("Exp", syntactic);
	    TreeNode* children[] = {$1, $2, $3};
	    node_insert(3, $$, children);
    }
    | Exp STAR Exp{
        $$ = node_init("Exp", syntactic);
	    TreeNode* children[] = {$1, $2, $3};
	    node_insert(3, $$, children);
    }
    | Exp DIV Exp{
        $$ = node_init("Exp", syntactic);
	    TreeNode* children[] = {$1, $2, $3};
	    node_insert(3, $$, children);
    }
    | LP Exp RP{
        $$ = node_init("Exp", syntactic);
	    TreeNode* children[] = {$1, $2, $3};
	    node_insert(3, $$, children);
    }
    | MINUS Exp{
        $$ = node_init("Exp", syntactic);
	    TreeNode* children[] = {$1, $2};
	    node_insert(2, $$, children);
    }
    | NOT Exp{
        $$ = node_init("Exp", syntactic);
	    TreeNode* children[] = {$1, $2};
	    node_insert(2, $$, children);
    }
    | ID LP Args RP{
        $$ = node_init("Exp", syntactic);
	    TreeNode* children[] = {$1, $2, $3, $4};
	    node_insert(4, $$, children);
    }
    | ID LP RP{
        $$ = node_init("Exp", syntactic);
	    TreeNode* children[] = {$1, $2, $3};
	    node_insert(3, $$, children);
    }
    | Exp LB Exp RB{
        $$ = node_init("Exp", syntactic);
	    TreeNode* children[] = {$1, $2, $3, $4};
	    node_insert(4, $$, children);
    }
    //| Exp LB error RB
    | Exp DOT ID{
        $$ = node_init("Exp", syntactic);
	    TreeNode* children[] = {$1, $2, $3};
	    node_insert(3, $$, children);
    }
    | ID{
        $$ = node_init("Exp", syntactic);
		TreeNode* children[] = {$1};
		node_insert(1, $$, children);
    }
    | INT{
        $$ = node_init("Exp", syntactic);
		TreeNode* children[] = {$1};
		node_insert(1, $$, children);
    }
    | FLOAT{
        $$ = node_init("Exp", syntactic);
		TreeNode* children[] = {$1};
		node_insert(1, $$, children);
    }
    | Exp ASSIGNOP error{
        Error++;
        print_error("Syntax error.");
    }
    | Exp AND error{
        Error++;
        print_error("Syntax error.");
        }
    | Exp OR error{
        Error++;
        print_error("Syntax error.");
        }
    | Exp RELOP error{
        Error++;
        print_error("Syntax error.");
        }
    | Exp PLUS error{
        Error++;
        print_error("Syntax error.");
        }
    | Exp MINUS error{
        Error++;
        print_error("Syntax error."); 
        }
    | Exp STAR error{
        Error++;
        print_error("Syntax error."); 
        }
    | Exp DIV error{
       Error++;
        print_error("Syntax error."); 
        }
    | MINUS error{
        Error++;
        print_error("Syntax error.");
        }
    | NOT error{
        Error++;
        print_error("Syntax error."); 
        }
    | STAR DIV error{
        Error++;
        print_error("Syntax error."); 
    }
    | ID LP error SEMI{
        Error++;
        print_error("Missing \")\"."); 
        }
    | Exp LB error RB{
        Error++;
        print_error("Missing \"]\".");
        }
    | Exp LB error SEMI{
        Error++;
        print_error("Missing \"]\".");
        }
    ;
Args : Exp COMMA Args{
    $$ = node_init("Args", syntactic);
	TreeNode* children[] = {$1, $2, $3};
	node_insert(3, $$, children);
}
    | Exp{
        $$ = node_init("Args", syntactic);
	    TreeNode* children[] = {$1};
	    node_insert(1, $$, children);
    }
    |error COMMA{
        Error++;
        print_error("Syntax error.");
    }
    ;

%%

void yyerror(char *msg){
  //printf("Error type B at Line %d: %s\n", yylineno, msg);
}
void print_error(char* msg){
    printf("Error type B at Line %d: %s\n", yylineno, msg);
}