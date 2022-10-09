%{
    #include <stdio.h>
    #include <stdlib.h>
    #include<string.h>
    #include "syntaxTree.h"
    #include "lex.yy.c"
    int Error = 0;
    extern int yylineno;
    int yyerror(char *msg);
%}

%locations

%union  {
    struct TreeNode* treeNode;
}

//terminal token
//%token <type_int> INT
//%token <type_float> FLOAT
//%token <type_str> ID SEMI COMMA ASSIGNOP RELOP
//%token <type_str> PLUS MINUS STAR DIV 
//%token <type_str> AND OR DOT NOT 
//%token <type_str> TYPE
//%token <type_str> LP RP LB RB LC RC 
//%token <type_str> STRUCT RETURN IF ELSE WHILE
%token <treeNode> INT FLOAT
%token <treeNode> ID SEMI COMMA ASSIGNOP RELOP PLUS MINUS STAR DIV AND OR DOT NOT
%token <treeNode> TYPE LP RP LB RB LC RC STRUCT RETURN IF ELSE WHILE

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
struct TreeNode* children[] = {$1};
node_insert(1, treeRoot, children);
}
    ;
ExtDefList : ExtDef ExtDefList{
    $$ = node_init("ExtDefList", syntactic);
    struct TreeNode* children[] = {$1, $2};
    node_insert(2, $$, children);
}
    |  {/* empty*/
    $$ = node_init("ExtDecList", syntactic);
}
    ;     
ExtDef : Specifier ExtDecList SEMI{
    $$ = node_init("ExtDef", syntactic);
    struct TreeNode* children[] = {$1, $2, $3};
    node_insert(3, $$, children);
}
    | Specifier SEMI{
        $$ = node_init("ExtDef", syntactic);
        struct TreeNode* children[] = {$1, $2};
        node_insert(2, $$, children);
    }
    | Specifier FunDec CompSt{
        $$ = node_init("ExtDef", syntactic);
        struct TreeNode* children[] = {$1, $2, $3};
        node_insert(3, $$, children);
    }
    | error SEMI{      /*Syntax error*/
        Error++;
    }
    ;
ExtDecList : VarDec{
    $$ = node_init("ExtDecList", syntactic);
    struct TreeNode *children[] = {$1};
    node_insert(1, $$, children);
}
    | VarDec COMMA ExtDecList{
        $$ = node_init("ExtDecList", syntactic);
	    struct TreeNode *children[] = {$1, $2, $3};
		node_insert(3, $$, children);
    }
    ;

//Specifiers
Specifier : TYPE{
    $$ = node_init("Specifier", syntactic);
	struct TreeNode *children[] = {$1};
	node_insert(1, $$, children);
}
    | StructSpecifier{
        $$ = node_init("Specifier", syntactic);
		struct TreeNode *children[] = {$1};
		node_insert(1, $$, children);		
    }
    ;   
StructSpecifier : STRUCT OptTag LC DefList RC{
    $$ = node_init("StructSpecifier", syntactic);
	struct TreeNode *children[] = {$1, $2, $3, $4, $5};
	node_insert(5, $$, children);
}
    | STRUCT Tag{
        $$ = node_init("StructSpecifier", syntactic);
		struct TreeNode *children[] = {$1, $2};
		node_insert(2, $$, children);
    }
    ;
OptTag : ID{
    $$ = node_init("OptTag", syntactic);
	struct TreeNode *children[] = {$1};
	node_insert(1, $$, children);
}
    | {/* empty*/
        $$ = node_init("OptTag", syntactic);
    }
    ;
Tag : ID{
    $$ = node_init("Tag", syntactic);
	struct TreeNode *children[] = {$1};
	node_insert(1, $$, children);
}
    ;

//Declarators
VarDec : ID{
    $$ = node_init("VarDec", syntactic);
	struct TreeNode *children[] = {$1};
	node_insert(1, $$, children);
}
    | VarDec LB INT RB{
        $$ = node_init("VarDec", syntactic);
		struct TreeNode *children[] = {$1, $2, $3, $4};
		node_insert(4, $$, children);
    }
    | VarDec LB error RB { /*Missing "]".*/
        Error++;
    }
    ;
FunDec : ID LP VarList RP{
    $$ = node_init("FunDec", syntactic);
	struct TreeNode *children[] = {$1, $2, $3, $4};
	node_insert(4, $$, children);
}
    | ID LP RP{
        $$ = node_init("FunDec", syntactic);
		struct TreeNode *children[] = {$1, $2, $3};
		node_insert(3, $$, children);
    }
    | error RP{
        Error++;
    }
    ;
VarList : ParamDec COMMA VarList{
    $$ = node_init("VarList", syntactic);
	struct TreeNode* children[] = {$1, $2, $3};
	node_insert(3, $$, children);
}
    | ParamDec{
        $$ = node_init("VarList", syntactic);
		struct TreeNode* children[] = {$1};
        node_insert(1, $$, children);
    }
    ;          
ParamDec : Specifier VarDec{
    $$ = node_init("ProgramDec", syntactic);
	struct TreeNode *children[] = {$1, $2};
	node_insert(2, $$, children);
}
    //| error COMMA
    //| error RP
    ;

//Statements
CompSt : LC DefList StmtList RC{
    $$ = node_init("CompSt", syntactic);
	struct TreeNode* children[] = {$1, $2, $3, $4};
	node_insert(4, $$, children);
}
    //| LC error RC 
    ;  
StmtList : Stmt StmtList{
    $$ = node_init("StmtList", syntactic);
	struct TreeNode *children[] = {$1, $2};
	node_insert(2, $$, children);
}
    | {/*empty*/
        $$ = node_init("StmtList", syntactic);
    }
    ;
Stmt : Exp SEMI{
    $$ = node_init("Stmt", syntactic);
	struct TreeNode* children[] = {$1, $2};
	node_insert(2, $$, children);
}
    | CompSt{
        $$ = node_init("Stmt", syntactic);
		struct TreeNode* children[] = {$1};
		node_insert(1, $$, children);
    }
    | RETURN Exp SEMI{
        $$ = node_init("Stmt", syntactic);
		struct TreeNode* children[] = {$1, $2, $3};
		node_insert(3, $$, children);
    }
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE{
        $$ = node_init("Stmt", syntactic);
	    struct TreeNode* children[] = {$1, $2, $3, $4, $5};
		node_insert(5, $$, children);
    }
    | IF LP Exp RP Stmt ELSE Stmt{
        $$ = node_init("Stmt", syntactic);
		struct TreeNode* children[] = {$1, $2, $3, $4, $5, $6, $7};
		node_insert(7, $$, children);
    }
    //| IF LP Exp RP error ELSE Stmt
    | WHILE LP Exp RP Stmt{
        $$ = node_init("Stmt", syntactic);
		struct TreeNode* children[] = {$1, $2, $3, $4, $5};
		node_insert(5, $$, children);
    }
    ;

//Local Definitions
DefList : Def DefList{
    $$ = node_init("DefList", syntactic);
	struct TreeNode* children[] = {$1, $2};
	node_insert(2, $$, children);
}
    | {/*empty*/
        $$ = node_init("DefList", syntactic);
    }
    ;    
Def : Specifier DecList SEMI{
    $$ = node_init("Def", syntactic);
	struct TreeNode* children[] = {$1, $2, $3};
	node_insert(3, $$, children);
}
    //| error SEMI
    ;
DecList : Dec{
    $$ = node_init("DecList", syntactic);
	struct TreeNode* children[] = {$1};
	node_insert(1, $$, children);
}
    | Dec COMMA DecList{
        $$ = node_init("DecList", syntactic);
		struct TreeNode* children[] = {$1, $2, $3};
		node_insert(3, $$, children);
    }
    ;
Dec : VarDec{
    $$ = node_init("Dec", syntactic);
	struct TreeNode* children[] = {$1};
	node_insert(1, $$, children);
}
    | VarDec ASSIGNOP Exp{
        $$ = node_init("Dec", syntactic);
		struct TreeNode* children[] = {$1, $2, $3};
		node_insert(3, $$, children);
    }
    ;
                
//Expressions
Exp : Exp ASSIGNOP Exp{
    $$ = node_init("Exp", syntactic);
	struct TreeNode* children[] = {$1, $2, $3};
	node_insert(3, $$, children);
}
    | Exp AND Exp{
        $$ = node_init("Exp", syntactic);
	    struct TreeNode* children[] = {$1, $2, $3};
	    node_insert(3, $$, children);
    }
    | Exp OR Exp{
        $$ = node_init("Exp", syntactic);
	    struct TreeNode* children[] = {$1, $2, $3};
	    node_insert(3, $$, children);
    }
    | Exp RELOP Exp{
        $$ = node_init("Exp", syntactic);
	    struct TreeNode* children[] = {$1, $2, $3};
	    node_insert(3, $$, children);
    }
    | Exp PLUS Exp{
        $$ = node_init("Exp", syntactic);
	    struct TreeNode* children[] = {$1, $2, $3};
	    node_insert(3, $$, children);
    }
    | Exp MINUS Exp{
        $$ = node_init("Exp", syntactic);
	    struct TreeNode* children[] = {$1, $2, $3};
	    node_insert(3, $$, children);
    }
    | Exp STAR Exp{
        $$ = node_init("Exp", syntactic);
	    struct TreeNode* children[] = {$1, $2, $3};
	    node_insert(3, $$, children);
    }
    | Exp DIV Exp{
        $$ = node_init("Exp", syntactic);
	    struct TreeNode* children[] = {$1, $2, $3};
	    node_insert(3, $$, children);
    }
    | LP Exp RP{
        $$ = node_init("Exp", syntactic);
	    struct TreeNode* children[] = {$1, $2, $3};
	    node_insert(3, $$, children);
    }
    | MINUS Exp{
        $$ = node_init("Exp", syntactic);
	    struct TreeNode* children[] = {$1, $2};
	    node_insert(2, $$, children);
    }
    | NOT Exp{
        $$ = node_init("Exp", syntactic);
	    struct TreeNode* children[] = {$1, $2};
	    node_insert(2, $$, children);
    }
    | ID LP Args RP{
        $$ = node_init("Exp", syntactic);
	    struct TreeNode* children[] = {$1, $2, $3, $4};
	    node_insert(4, $$, children);
    }
    | ID LP RP{
        $$ = node_init("Exp", syntactic);
	    struct TreeNode* children[] = {$1, $2, $3};
	    node_insert(3, $$, children);
    }
    | Exp LB Exp RB{
        $$ = node_init("Exp", syntactic);
	    struct TreeNode* children[] = {$1, $2, $3, $4};
	    node_insert(4, $$, children);
    }
    //| Exp LB error RB
    | Exp DOT ID{
        $$ = node_init("Exp", syntactic);
	    struct TreeNode* children[] = {$1, $2, $3};
	    node_insert(3, $$, children);
    }
    | ID{
        $$ = node_init("Exp", syntactic);
		struct TreeNode* children[] = {$1};
		node_insert(1, $$, children);
    }
    | INT{
        $$ = node_init("Exp", syntactic);
		struct TreeNode* children[] = {$1};
		node_insert(1, $$, children);
    }
    | FLOAT{
        $$ = node_init("Exp", syntactic);
		struct TreeNode* children[] = {$1};
		node_insert(1, $$, children);
    }
    ;
Args : Exp COMMA Args{
    $$ = node_init("Args", syntactic);
	struct TreeNode* children[] = {$1, $2, $3};
	node_insert(3, $$, children);
}
    | Exp{
        $$ = node_init("Args", syntactic);
	    struct TreeNode* children[] = {$1};
	    node_insert(1, $$, children);
    }
    ;

%%

int yyerror(char *msg){
  fprintf(stderr, "Error type B at Line %d: %s\n", yylineno, msg);
}
