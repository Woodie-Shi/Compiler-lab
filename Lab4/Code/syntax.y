%{
    #include <stdio.h>
    #include "syntaxTree.h"
    #include "lex.yy.c"
    extern int syntax_errs;
    extern int yylineno;
    extern char* yytext;
    int yyerr_line=0;
    void yyerror(const char *msg);
    int yylex();
    extern Node root;
%}

%locations

%union {
    struct treenode_* node;
}

//terminal token
//%token <type_int> INT
//%token <type_float> FLOAT
//%token <type_str> ID SEMI COMMA ASSIGNOP RELOP
//%token <type_str> PLUS MINUS STAR DIV 
//%token <type_str> AND OR DOT NOT LP RP LB RB LC RC
//%token <type_str> STRUCT RETURN IF ELSE WHILE
%token <node> INT FLOAT 
%token <node> ID SEMI COMMA ASSIGNOP RELOP
%token <node> PLUS MINUS STAR DIV 
%token <node> AND OR NOT DOT
%token <node> TYPE
%token <node> LP RP LB RB LC RC
%token <node> STRUCT RETURN IF ELSE WHILE

//non-terminal type
//%type <type_str> Program ExtDefList ExtDef ExtDecList Specifier
//%type <type_str> StructSpecifier OptTag Tag VarDec FunDec VarList
//%type <type_str> ParamDec CompSt StmtList Stmt DefList Def DecList
//%type <type_str> Dec Exp Args
%type <node> Program ExtDefList ExtDef ExtDecList Specifier
%type <node> StructSpecifier OptTag Tag VarDec FunDec VarList
%type <node> ParamDec CompSt StmtList Stmt DefList Def DecList
%type <node> Dec Exp Args

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
    $$=nonterminal_node("Program",@$.first_line,1,$1);
    root=$$; 
}
;               
ExtDefList: ExtDef ExtDefList   { 
    $$=nonterminal_node("ExtDefList",@$.first_line,2,$1,$2); 
}
    | /* empty */{ $$=NULL; }
;               
ExtDef: Specifier ExtDecList SEMI   { 
    $$=nonterminal_node("ExtDef",@$.first_line,3,$1,$2,$3); 
}
    | Specifier SEMI    { 
        $$=nonterminal_node("ExtDef",@$.first_line,2,$1,$2); 
    }
    | Specifier FunDec CompSt   { 
        $$=nonterminal_node("ExtDef",@$.first_line,3,$1,$2,$3); 
    }
    | error CompSt  { yyerrok; }
    | error SEMI    { yyerrok; }
    | Specifier error SEMI  { yyerrok; }
    | Specifier error CompSt    { yyerrok; }
;               
ExtDecList: VarDec  { 
    $$=nonterminal_node("ExtDecList",@$.first_line,1,$1); 
}
    | VarDec COMMA ExtDecList   { 
        $$=nonterminal_node("ExtDecList",@$.first_line,3,$1,$2,$3); 
    }
;
/* Specifiers */
Specifier: TYPE { 
    $$=nonterminal_node("Specifier",@$.first_line,1,$1); 
    }
    | StructSpecifier   {
        $$=nonterminal_node("Specifier",@$.first_line,1,$1); 
    }
;
StructSpecifier: STRUCT OptTag LC DefList RC    { 
    $$=nonterminal_node("StructSpecifier",@$.first_line,5,$1,$2,$3,$4,$5); 
    }
    | STRUCT Tag    { 
        $$=nonterminal_node("StructSpecifier",@$.first_line,2,$1,$2); 
    }
    | STRUCT OptTag LC DefList error RC { yyerrok; }
;   
OptTag: ID  { 
    $$=nonterminal_node("OptTag",@$.first_line,1,$1); 
    }
    | /* empty */   { $$=NULL; }
;
Tag: ID { 
    $$=nonterminal_node("Tag",@$.first_line,1,$1); 
}
;
/* Declarators */
VarDec: ID  { 
    $$=nonterminal_node("VarDec",@$.first_line,1,$1); 
}
    | VarDec LB INT RB  { 
        $$=nonterminal_node("VarDec",@$.first_line,4,$1,$2,$3,$4); 
    }
;               
FunDec: ID LP VarList RP    { 
    $$=nonterminal_node("FunDec",@$.first_line,4,$1,$2,$3,$4); 
}
    | ID LP RP  { 
        $$=nonterminal_node("FunDec",@$.first_line,3,$1,$2,$3); 
    }
;
VarList: ParamDec COMMA VarList{ 
    $$=nonterminal_node("VarList",@$.first_line,3,$1,$2,$3); 
}
    | ParamDec  { 
        $$=nonterminal_node("VarList",@$.first_line,1,$1); 
    }
;
ParamDec: Specifier VarDec  { 
    $$=nonterminal_node("ParamDec",@$.first_line,2,$1,$2); 
}
;
/* Statements */
CompSt: LC DefList StmtList RC  { 
    $$=nonterminal_node("CompSt",@$.first_line,4,$1,$2,$3,$4); 
}
;
StmtList: Stmt StmtList { 
    $$=nonterminal_node("StmtList",@$.first_line,2,$1,$2); 
}
    | /* empty */   { $$=NULL; }
;
Stmt: Exp SEMI  { 
    $$=nonterminal_node("Stmt",@$.first_line,2,$1,$2); 
}
    | CompSt    {
        $$=nonterminal_node("Stmt",@$.first_line,1,$1); 
    }
    | RETURN Exp SEMI   { 
        $$=nonterminal_node("Stmt",@$.first_line,3,$1,$2,$3); 
    }
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE   { 
        $$=nonterminal_node("Stmt",@$.first_line,5,$1,$2,$3,$4,$5); 
    }
    | IF LP Exp RP Stmt ELSE Stmt   { 
        $$=nonterminal_node("Stmt",@$.first_line,7,$1,$2,$3,$4,$5,$6,$7); 
    }
    | WHILE LP Exp RP Stmt  { 
        $$=nonterminal_node("Stmt",@$.first_line,5,$1,$2,$3,$4,$5);
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
    $$=nonterminal_node("DefList",@$.first_line,2,$1,$2); 
}
    | /* empty */   { $$=NULL; }
;
Def: Specifier DecList SEMI { 
    $$=nonterminal_node("Def",@$.first_line,3,$1,$2,$3); 
}
    | Specifier DecList error SEMI  { yyerrok; }
    | Specifier error SEMI  { yyerrok; }
;
DecList: Dec    { 
    $$=nonterminal_node("DecList",@$.first_line,1,$1); 
}
    | Dec COMMA DecList { 
        $$=nonterminal_node("DecList",@$.first_line,3,$1,$2,$3); 
    }
;
Dec: VarDec { 
    $$=nonterminal_node("Dec",@$.first_line,1,$1); 
}
    | VarDec ASSIGNOP Exp   { 
        $$=nonterminal_node("Dec",@$.first_line,3,$1,$2,$3); 
    }
;
/* Expressions */
Exp: Exp ASSIGNOP Exp   { 
    $$=nonterminal_node("Exp",@$.first_line,3,$1,$2,$3); 
}
    | Exp AND Exp   { 
        $$=nonterminal_node("Exp",@$.first_line,3,$1,$2,$3); 
    }
    | Exp OR Exp    { 
        $$=nonterminal_node("Exp",@$.first_line,3,$1,$2,$3); 
    }
    | Exp RELOP Exp { 
        $$=nonterminal_node("Exp",@$.first_line,3,$1,$2,$3); 
    }
    | Exp PLUS Exp  { 
        $$=nonterminal_node("Exp",@$.first_line,3,$1,$2,$3);
    }
    | Exp MINUS Exp { 
        $$=nonterminal_node("Exp",@$.first_line,3,$1,$2,$3); 
    }
    | Exp STAR Exp  { 
        $$=nonterminal_node("Exp",@$.first_line,3,$1,$2,$3); 
    }
    | Exp DIV Exp   { 
        $$=nonterminal_node("Exp",@$.first_line,3,$1,$2,$3); 
    }
    | LP Exp RP { 
        $$=nonterminal_node("Exp",@$.first_line,3,$1,$2,$3); 
    }
    | MINUS Exp %prec UMINUS    { 
        $$=nonterminal_node("Exp",@$.first_line,2,$1,$2); 
    }
    | NOT Exp   { 
        $$=nonterminal_node("Exp",@$.first_line,2,$1,$2); 
    }
    | ID LP Args RP { 
        $$=nonterminal_node("Exp",@$.first_line,4,$1,$2,$3,$4); 
    }
    | ID LP RP  { 
        $$=nonterminal_node("Exp",@$.first_line,3,$1,$2,$3); 
    }
    | Exp LB Exp RB { 
        $$=nonterminal_node("Exp",@$.first_line,4,$1,$2,$3,$4); 
    }
    | Exp DOT ID    { 
        $$=nonterminal_node("Exp",@$.first_line,3,$1,$2,$3); 
    }
    | ID    { 
        $$=nonterminal_node("Exp",@$.first_line,1,$1); 
    }
    | INT   { 
        $$=nonterminal_node("Exp",@$.first_line,1,$1); 
    }
    | FLOAT { 
        $$=nonterminal_node("Exp",@$.first_line,1,$1);
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
    $$=nonterminal_node("Args",@$.first_line,3,$1,$2,$3); 
}
    | Exp   { 
        $$=nonterminal_node("Args",@$.first_line,1,$1);
    }
    | error COMMA Exp   {}
;
%%

void yyerror(const char *msg) {
    if(yyerr_line == yylineno)return;
    yyerr_line=yylineno;
    syntax_errs++;
    printf("Error type B at Line %d: %s\n", yylineno, msg);
}