%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "lex.yy.c"
    extern int yylineno;
    int yyerror(char *msg);
%}

%locations

%union  {
  int type_int;
  float type_float;
  char type_str[32];
}

//terminal token
%token <type_int> INT
%token <type_float> FLOAT
%token <type_str> ID SEMI COMMA ASSIGNOP RELOP
%token <type_str> PLUS MINUS STAR DIV 
%token <type_str> AND OR DOT NOT 
%token <type_str> TYPE
%token <type_str> LP RP LB RB LC RC 
%token <type_str> STRUCT RETURN IF ELSE WHILE

//non-terminal type
%type <type_str> Program ExtDefList ExtDef ExtDecList Specifier
%type <type_str> StructSpecifier OptTag Tag VarDec FunDec VarList
%type <type_str> ParamDec CompSt StmtList Stmt DefList Def DecList
%type <type_str> Dec Exp Args

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
Program : ExtDefList
    ;
ExtDefList : ExtDef ExtDefList
    |  /* empty*/
    ;     
ExtDef : Specifier ExtDecList SEMI
    | Specifier SEMI
    | Specifier FunDec CompSt
    //| error SEMI      /*Syntax error*/
    ;
ExtDecList : VarDec
    | VarDec COMMA ExtDecList
    ;

//Specifiers
Specifier : TYPE
    | StructSpecifier
    ;   
StructSpecifier : STRUCT OptTag LC DefList RC
    | STRUCT Tag
    ;
OptTag : ID 
    | /* empty*/
    ;
Tag : ID
    ;

//Declarators
VarDec : ID
    | VarDec LB INT RB
    //| VarDec LB error RB  /*Missing "]".*/
    ;
FunDec : ID LP VarList RP
    | ID LP RP
    //| error RP
    ;
VarList : ParamDec COMMA VarList
    | ParamDec
    ;          
ParamDec : Specifier VarDec
    //| error COMMA
    //| error RP
    ;

//Statements
CompSt : LC DefList StmtList RC
    //| LC error RC 
    ;  
StmtList : Stmt StmtList
    | /*empty*/
    ;
Stmt : Exp SEMI
    | CompSt
    | RETURN Exp SEMI
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE
    | IF LP Exp RP Stmt ELSE Stmt
    //| IF LP Exp RP error ELSE Stmt
    | WHILE LP Exp RP Stmt
    ;

//Local Definitions
DefList : Def DefList
    | /*empty*/
    ;    
Def : Specifier DecList SEMI
    //| error SEMI              {errorNum++;myerror("Syntax error.");}
    ;
DecList : Dec
    | Dec COMMA DecList
    ;
Dec : VarDec
    | VarDec ASSIGNOP Exp
    ;
                
//Expressions
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
    | Exp LB error RB
    | Exp DOT ID
    | ID
    | INT
    | FLOAT
    ;
Args : Exp COMMA Args
    | Exp
    ;

%%

int yyerror(char *msg){
  fprintf(stderr, "error: %s\n", msg);
}
