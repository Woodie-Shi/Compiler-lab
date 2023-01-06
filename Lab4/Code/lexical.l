%{
    //#define SHOW_INFO
    #include <stdio.h>
    #include <stdlib.h>
    #include<stdint.h>
    #include "syntax.tab.h"
    #include "syntaxTree.h"
    extern int lexical_errs;
    extern YYSTYPE yylval;
    int yycolumn = 1;

    #define YY_USER_ACTION \
    yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; \
    yylloc.last_column = yycolumn + yyleng - 1; \
    yycolumn += yyleng;

    void show_info(char *str);
    int yylex();
    void show_lexerr(char *msg);
    void add_node(const char* name, enum syntax_type datatype, const char* val);
%}
%option yylineno


OCT 0[0-7]+
WRONG_OCT 0[0-7]*[8-9]+[0-9]*
DEC 0|[1-9][0-9]*
WRONG_DEC [0-9]+[AaC-Wc-wY-Zy-z]+[0-9A-Da-dF-Zf-z]*
HEX 0[xX][0-9a-fA-F]+
WRONG_HEX 0[xX][0-9a-fA-F]*[g-zG-Z]+[0-9a-fA-F]*|0[xX]

FLOAT ([0-9]+\.[0-9]*|\.[0-9]+)([eE][+-]?[0-9]+)?
WRONG_FLOAT ([0-9]+\.[0-9]*|\.[0-9]+)[eE][+-]?([0-9]+\.[0-9]*|\.[0-9]+)|([0-9]+\.[0-9]*|\.[0-9]+)[eE][+-]?

ID [A-Za-z_][0-9A-Za-z_]*

SEMI ;
COMMA ,
ASSIGNOP =
RELOP >|<|>=|<=|==|!=
PLUS "+"
MINUS "-"
STAR "*"
DIV "/"
AND "&&"
OR "||"
DOT "."
NOT "!"
TYPE int|float
LP \(
RP \)
LB \[
RB \]
LC \{
RC \}
STRUCT struct
RETURN return
IF if
ELSE else
WHILE while
SPACE [  \r\t]+

%%
{OCT}   {
    show_info("OCT");
    //uint32_t val = 0;
    /*yylval.treeNode = node_init("INT", lexical);
    sscanf(yytext,"%o", &yylval.treeNode->val_int);
    //printf("val: %u\n", val);*/
    add_node("INT", TYPE_OCT, yytext);
    show_lexerr("illegal int");
    return INT;
}
{WRONG_OCT} {
    /*printf("Error type A at Line %d: Illegal octal number \'%s\'.\n",yylineno, yytext);
    yylval.treeNode = node_init("INT", lexical);
    yylval.treeNode->val_int = 0;
    Error++;*/
    add_node("INT", TYPE_OCT, yytext);
    show_lexerr("illegal int");
    return INT;
}
{DEC}   {   
    show_info("DEC");
    //uint32_t val = 0;
    /*yylval.treeNode = node_init("INT", lexical);
    sscanf(yytext,"%d", &yylval.treeNode->val_int);
    //printf("val: %u\n", val);*/
    add_node("INT", TYPE_INT, yytext);
    return INT;
}
{WRONG_DEC} {
    /*printf("Error type A at Line %d: Illegal decimal number \'%s\'.\n",yylineno, yytext);
    yylval.treeNode = node_init("INT", lexical);
    yylval.treeNode->val_int = 0;
    Error++;*/
    add_node("INT", TYPE_INT, yytext);
    show_lexerr("illegal int");
    return INT;
}
{HEX}   {
    show_info("HEX");
    //uint32_t val = 0;
    /*yylval.treeNode = node_init("INT", lexical);
    sscanf(yytext,"%x", &yylval.treeNode->val_int);
    //printf("val: %u\n", val);*/
    add_node("INT", TYPE_HEX, yytext);
    show_lexerr("illegal int");
    return INT;
}
{WRONG_HEX} {
    /*printf("Error type A at Line %d: Illegal hexadecimal number '%s'\n", yylineno, yytext);
    yylval.treeNode = node_init("INT", lexical);
    yylval.treeNode->val_int = 0;
    Error++;*/
    add_node("INT", TYPE_HEX, yytext);
    show_lexerr("illegal int");
    return INT;
}

{FLOAT}     {
    show_info("FLOAT");
    //float val = 0;
    /*yylval.treeNode = node_init("FLOAT", lexical);
    sscanf(yytext,"%f", &yylval.treeNode->val_float);
    //printf("val: %f\n", val);*/
    add_node("FLOAT", TYPE_FLOAT, yytext);
    return FLOAT;
}
{WRONG_FLOAT}   {
    /*printf("Error type A at Line %d: Illegal floating point number \'%s\'.\n",yylineno, yytext);
    yylval.treeNode = node_init("FLOAT", lexical);
    yylval.treeNode->val_float = 0;
    Error++;*/
    add_node("FLOAT", TYPE_FLOAT, yytext);
    show_lexerr("illegal float");
    return FLOAT;
}

{SEMI}  {
    show_info("SEMI");
    /*yylval.treeNode = node_init("SEMI", lexical);
    yylval.treeNode->val_str = (char*)malloc(yyleng);
    strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("SEMI", OTHER, NULL);
    return SEMI;
}
{COMMA} {
    show_info("COMMA");
    /*yylval.treeNode = node_init("COMMA", lexical);
    yylval.treeNode->val_str = (char*)malloc(yyleng);
    strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("COMMA", OTHER, NULL);
    return COMMA;
}
{ASSIGNOP} {
    show_info("ASSIGNOP");
   /*yylval.treeNode = node_init("ASSIGNOP", lexical);
   yylval.treeNode->val_str = (char*)malloc(yyleng);
   strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("ASSIGNOP", OTHER, NULL);
    return ASSIGNOP;
}
{RELOP} {
    show_info("RELOP");
    /*yylval.treeNode = node_init("RELOP", lexical);
    yylval.treeNode->val_str = (char*)malloc(yyleng);
    strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("RELOP", OTHER, yytext);
    return RELOP;
}
{PLUS}  {
    show_info("PLUS");
    /*yylval.treeNode = node_init("PLUS", lexical);
    yylval.treeNode->val_str = (char*)malloc(yyleng);
    strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("PLUS", OTHER, yytext);
    return PLUS;
}
{MINUS} {
    show_info("MINUS");
    /*yylval.treeNode = node_init("MINUS", lexical);
    yylval.treeNode->val_str = (char*)malloc(yyleng);
    strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("MINUS", OTHER, NULL);
    return MINUS;
}
{STAR}  {
    show_info("STAR");
    /*yylval.treeNode = node_init("STAR", lexical);
    yylval.treeNode->val_str = (char*)malloc(yyleng);
    strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("STAR", OTHER, NULL); 
    return STAR;
}
{DIV}   {
    show_info("DIV");
    /*yylval.treeNode = node_init("DIV", lexical);
    yylval.treeNode->val_str = (char*)malloc(yyleng);
    strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("DIV", OTHER, NULL); 
    return DIV;
}
{AND}   {
    show_info("AND");
    /*yylval.treeNode = node_init("AND", lexical);
    yylval.treeNode->val_str = (char*)malloc(yyleng);
    strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("AND", OTHER, NULL); 
    return AND;
}
{OR}    {
    show_info("OR");
    /*yylval.treeNode = node_init("OR", lexical);
    yylval.treeNode->val_str = (char*)malloc(yyleng);
    strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("OR", OTHER, NULL); 
    return OR;
}
{DOT}   {
    show_info("DOT");
    /*yylval.treeNode = node_init("DOT", lexical);
    yylval.treeNode->val_str = (char*)malloc(yyleng);
    strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("DOT", OTHER, NULL); 
    return DOT;
}
{NOT}   {
    show_info("NOT");
    /*yylval.treeNode = node_init("NOT", lexical);
    yylval.treeNode->val_str = (char*)malloc(yyleng);
    strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("NOT", OTHER, NULL); 
    return NOT;
}
{TYPE}  {
    show_info("TYPE");
    /*yylval.treeNode = node_init("TYPE", lexical);
    yylval.treeNode->val_str = (char*)malloc(yyleng);
    strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("TYPE", TYPE_TYPE, yytext);
    return TYPE;
}
{LP}    {
    show_info("LP");
    /*yylval.treeNode = node_init("LP", lexical);
    yylval.treeNode->val_str = (char*)malloc(yyleng);
    strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("LP", OTHER, NULL);
    return LP;
}
{RP}        {
    show_info("RP");
    /*yylval.treeNode = node_init("RP", lexical);
    yylval.treeNode->val_str = (char*)malloc(yyleng);
    strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("RP", OTHER, NULL);
    return RP;
}
{LB}    {
    show_info("LB");
    /*yylval.treeNode = node_init("LB", lexical);
    yylval.treeNode->val_str = (char*)malloc(yyleng);
    strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("LB", OTHER, NULL);
    return LB;
}
{RB}    {
    show_info("RB");
    /*yylval.treeNode = node_init("RB", lexical);
    yylval.treeNode->val_str = (char*)malloc(yyleng);
    strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("RB", OTHER, NULL);
    return RB;
}
{LC}    {
    show_info("LC");
    /*yylval.treeNode = node_init("LC", lexical);
    yylval.treeNode->val_str = (char*)malloc(yyleng);
    strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("LC", OTHER, NULL);
    return LC;
}
{RC}    {
    show_info("RC");
    /*yylval.treeNode = node_init("RC", lexical);
    yylval.treeNode->val_str = (char*)malloc(yyleng);
    strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("RC", OTHER, NULL);
    return RC;
}
{STRUCT}    {
    show_info("STRUCT");
    /*yylval.treeNode = node_init("STRUCT", lexical);
    yylval.treeNode->val_str = (char*)malloc(yyleng);
    strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("STRUCT", OTHER, NULL);
    return STRUCT;
}
{RETURN}    {
    show_info("RETURN");
    /*yylval.treeNode = node_init("RETURN", lexical);
    yylval.treeNode->val_str = (char*)malloc(yyleng);
    strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("RETURN", OTHER, NULL);
    return RETURN;
}
{IF}    {
    show_info("IF");
    /*yylval.treeNode = node_init("IF", lexical);
    yylval.treeNode->val_str = (char*)malloc(yyleng);
    strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("IF", OTHER, NULL);
    return IF;
}
{ELSE}  {
    show_info("ELSE");
    /*yylval.treeNode = node_init("ELSE", lexical);
    yylval.treeNode->val_str = (char*)malloc(yyleng);
    strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("ELSE", OTHER, NULL);
    return ELSE;
}
{WHILE}     {
    show_info("WHILE");
    /*yylval.treeNode = node_init("WHILE", lexical);
    yylval.treeNode->val_str = (char*)malloc(yyleng);
    strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("WHILE", OTHER, NULL);
    return WHILE;
}
{ID}    {
    show_info("ID");
    /*yylval.treeNode = node_init("ID", lexical);
    yylval.treeNode->val_str = (char*)malloc(yyleng);
    strcpy(yylval.treeNode->val_str, yytext);*/
    add_node("ID", TYPE_ID, yytext);
    return ID;
}
"\n"    {
    yycolumn = 1;
}
{SPACE} {
    show_info("SPACE");
}

"/*"    {
    show_info("COMMENT");
    char cur = input();
    char nxt = input();
    while(cur != '*' || nxt != '/')
    {
        cur = nxt;
        nxt = input();
        if(nxt == '\0'){
            lexical_errs++;
            printf("Error type B at Line %d: syntax error, no match comment \"/*\".\n", yylineno);
            break;
        }
    }
}
"//"    {
    show_info("COMMENT");
    char c = input();
    while(c != '\n')  c = input();
}

. {
    /*Error++;
    printf("Error type A at line %d: Mysterious character \"%s\".\n",yylineno,yytext);*/
    show_lexerr("Mysterious characters");
}

%%

void show_info(char *str){
    #ifdef  SHOW_INFO
        printf("Line %d: input  %s : %s\n",yylineno, str, yytext);
    #endif
}

void show_lexerr(char *msg){
    lexical_errs++;
    printf("Error type A at Line %d: %s %s.\n", yylineno, msg ,yytext);
}

void add_node(const char* name, enum syntax_type datatype, const char* val) {
    yylval.treeNode = node_init(name, datatype, val);
    //tree_display(yylval.treeNode,0);
}
