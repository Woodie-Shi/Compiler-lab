%{
    #include <stdio.h>
    #include "syntaxTree.h"
    #include "lex.yy.c"
    extern int syntax_errs;
    extern int yylineno;
    void yyerror(const char *msg);
    int yylex();
    extern TreeNode root;
%}

%locations

%union {
    struct TreeNode_* treeNode;
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

%start Program

%right ASSIGNOP
%left  OR
%left  AND
%left  RELOP
%left  PLUS MINUS
%left  STAR DIV
%right NOT
%left  UMINUS 
%left  DOT LP RP LB RB
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%%
/* High-level Definitions */
Program: ExtDefList { 
    $$=node_insert("Program",@$.first_line,1,$1);
    root=$$; 
}
;               
ExtDefList: ExtDef ExtDefList   { 
    $$=node_insert("ExtDefList",@$.first_line,2,$1,$2); 
}
    | /* empty */{ $$=NULL; }
;               
ExtDef: Specifier ExtDecList SEMI   { 
    $$=node_insert("ExtDef",@$.first_line,3,$1,$2,$3); 
}
    | Specifier SEMI    { 
        $$=node_insert("ExtDef",@$.first_line,2,$1,$2); 
    }
    | Specifier FunDec CompSt   { 
        $$=node_insert("ExtDef",@$.first_line,3,$1,$2,$3); 
    }
;               
ExtDecList: VarDec  { 
    $$=node_insert("ExtDecList",@$.first_line,1,$1); 
}
    | VarDec COMMA ExtDecList   { 
        $$=node_insert("ExtDecList",@$.first_line,3,$1,$2,$3); 
    }
;
/* Specifiers */
Specifier: TYPE { 
    $$=node_insert("Specifier",@$.first_line,1,$1); 
    }
    | StructSpecifier   {
        $$=node_insert("Specifier",@$.first_line,1,$1); 
    }
;
StructSpecifier: STRUCT OptTag LC DefList RC    { 
    $$=node_insert("StructSpecifier",@$.first_line,5,$1,$2,$3,$4,$5); 
    }
    | STRUCT Tag    { 
        $$=node_insert("StructSpecifier",@$.first_line,2,$1,$2); 
    }
    | STRUCT OptTag LC DefList error RC { yyerrok; }
;   
OptTag: ID  { 
    $$=node_insert("OptTag",@$.first_line,1,$1); 
    }
    | /* empty */   { $$=NULL; }
;
Tag: ID { 
    $$=node_insert("Tag",@$.first_line,1,$1); 
}
;
/* Declarators */
VarDec: ID  { 
    $$=node_insert("VarDec",@$.first_line,1,$1); 
}
    | VarDec LB INT RB  { 
        $$=node_insert("VarDec",@$.first_line,4,$1,$2,$3,$4); 
    }
;               
FunDec: ID LP VarList RP    { 
    $$=node_insert("FunDec",@$.first_line,4,$1,$2,$3,$4); 
}
    | ID LP RP  { 
        $$=node_insert("FunDec",@$.first_line,3,$1,$2,$3); 
    }
;
VarList: ParamDec COMMA VarList{ 
    $$=node_insert("VarList",@$.first_line,3,$1,$2,$3); 
}
    | ParamDec  { 
        $$=node_insert("VarList",@$.first_line,1,$1); 
    }
;
ParamDec: Specifier VarDec  { 
    $$=node_insert("ParamDec",@$.first_line,2,$1,$2); 
}
;
/* Statements */
CompSt: LC DefList StmtList RC  { 
    $$=node_insert("CompSt",@$.first_line,4,$1,$2,$3,$4); 
}
;
StmtList: Stmt StmtList { 
    $$=node_insert("StmtList",@$.first_line,2,$1,$2); 
}
    | /* empty */   { $$=NULL; }
;
Stmt: Exp SEMI  { 
    $$=node_insert("Stmt",@$.first_line,2,$1,$2); 
}
    | CompSt    {
        $$=node_insert("Stmt",@$.first_line,1,$1); 
    }
    | RETURN Exp SEMI   { 
        $$=node_insert("Stmt",@$.first_line,3,$1,$2,$3); 
    }
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE   { 
        $$=node_insert("Stmt",@$.first_line,5,$1,$2,$3,$4,$5); 
    }
    | IF LP Exp RP Stmt ELSE Stmt   { 
        $$=node_insert("Stmt",@$.first_line,7,$1,$2,$3,$4,$5,$6,$7); 
    }
    | WHILE LP Exp RP Stmt  { 
        $$=node_insert("Stmt",@$.first_line,5,$1,$2,$3,$4,$5);
    }                       
    | error SEMI    { yyerrok; }
    | error Stmt    { yyerrok; }
    | Exp error {}
    | IF LP error RP Stmt %prec LOWER_THAN_ELSE {}
    | IF LP error RP Stmt ELSE Stmt {}
    | WHILE LP error RP Stmt    { yyerrok; }
;
/* Local Definitions */
DefList: Def DefList    { 
    $$=node_insert("DefList",@$.first_line,2,$1,$2); 
}
    | /* empty */   { $$=NULL; }
;
Def: Specifier DecList SEMI { 
    $$=node_insert("Def",@$.first_line,3,$1,$2,$3); 
}
    | Specifier DecList error SEMI  { yyerrok; }
    | Specifier error SEMI  { yyerrok; }
;
DecList: Dec    { 
    $$=node_insert("DecList",@$.first_line,1,$1); 
}
    | Dec COMMA DecList { 
        $$=node_insert("DecList",@$.first_line,3,$1,$2,$3); 
    }
;
Dec: VarDec { 
    $$=node_insert("Dec",@$.first_line,1,$1); 
}
    | VarDec ASSIGNOP Exp   { 
        $$=node_insert("Dec",@$.first_line,3,$1,$2,$3); 
    }
;
/* Expressions */
Exp: Exp ASSIGNOP Exp   { 
    $$=node_insert("Exp",@$.first_line,3,$1,$2,$3); 
}
    | Exp AND Exp   { 
        $$=node_insert("Exp",@$.first_line,3,$1,$2,$3); 
    }
    | Exp OR Exp    { 
        $$=node_insert("Exp",@$.first_line,3,$1,$2,$3); 
    }
    | Exp RELOP Exp { 
        $$=node_insert("Exp",@$.first_line,3,$1,$2,$3); 
    }
    | Exp PLUS Exp  { 
        $$=node_insert("Exp",@$.first_line,3,$1,$2,$3);
    }
    | Exp MINUS Exp { 
        $$=node_insert("Exp",@$.first_line,3,$1,$2,$3); 
    }
    | Exp STAR Exp  { 
        $$=node_insert("Exp",@$.first_line,3,$1,$2,$3); 
    }
    | Exp DIV Exp   { 
        $$=node_insert("Exp",@$.first_line,3,$1,$2,$3); 
    }
    | LP Exp RP { 
        $$=node_insert("Exp",@$.first_line,3,$1,$2,$3); 
    }
    | MINUS Exp %prec UMINUS    { 
        $$=node_insert("Exp",@$.first_line,2,$1,$2); 
    }
    | NOT Exp   { 
        $$=node_insert("Exp",@$.first_line,2,$1,$2); 
    }
    | ID LP Args RP { 
        $$=node_insert("Exp",@$.first_line,4,$1,$2,$3,$4); 
    }
    | ID LP RP  { 
        $$=node_insert("Exp",@$.first_line,3,$1,$2,$3); 
    }
    | Exp LB Exp RB { 
        $$=node_insert("Exp",@$.first_line,4,$1,$2,$3,$4); 
    }
    | Exp DOT ID    { 
        $$=node_insert("Exp",@$.first_line,3,$1,$2,$3); 
    }
    | ID    { 
        $$=node_insert("Exp",@$.first_line,1,$1); 
    }
    | INT   { 
        $$=node_insert("Exp",@$.first_line,1,$1); 
    }
    | FLOAT { 
        $$=node_insert("Exp",@$.first_line,1,$1);
    }
    | Exp ASSIGNOP error    {}  
    | Exp AND error {}    
    | Exp OR error  {}    
    | Exp RELOP error   {}    
    | Exp PLUS error    {}    
    | Exp MINUS error   {}  
    | Exp STAR error    {}    
    | Exp DIV error {}     
    | LP error RP   { yyerrok; }   
    | LP Exp error  {}    
    | MINUS error %prec UMINUS  {}           
    | NOT error {}  
    | ID LP error RP    { yyerrok; }  
    | Exp LB error RB   { yyerrok; }  
;
Args: Exp COMMA Args    { 
    $$=node_insert("Args",@$.first_line,3,$1,$2,$3); 
}
    | Exp   { 
        $$=node_insert("Args",@$.first_line,1,$1);
    }
    | error COMMA Exp   {}
;
%%

void yyerror(const char *msg) {
    syntax_errs++;
    printf("Error type B at Line %d: %s\n", yylineno, msg);
}