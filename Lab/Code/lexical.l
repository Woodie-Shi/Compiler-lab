%{
    #define SHOW_INFO
    #include <stdio.h>
    #include <stdlib.h>
    #include<stdint.h>
    int Lerror=0;
    void show_info(char *str);
%}
%option yylineno

BIN 0[bB][01]+
WRONG_BIN 0[bB][01]*[2-9a-zA-Z]+[0-9]*|[0-9][bB]
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
SPACE [  \r\n\t]+

%%
{BIN}   {
    show_info("BIN");
    uint32_t val = strtol(yytext, NULL, 2);
    printf("val: %u\n", val);
    //return INT;
}
{WRONG_BIN}   {
    printf("Error type A at Line %d: Illegal binary number \'%s\'.\n",yylineno, yytext);
    Lerror += 1;
    //return INT;
}
{OCT}   {
    show_info("OCT");
    uint32_t val = 0;
    sscanf(yytext,"%o", &val);
    printf("val: %u\n", val);
    //return INT;
}
{WRONG_OCT} {
    printf("Error type A at Line %d: Illegal octal number \'%s\'.\n",yylineno, yytext);
    Lerror += 1;
    //return INT;
}
{DEC}   {   
    show_info("DEC");
    uint32_t val = 0;
    sscanf(yytext,"%u", &val);
    printf("val: %u\n", val);
    //return INT;
}
{WRONG_DEC} {
    printf("Error type A at Line %d: Illegal decimal number \'%s\'.\n",yylineno, yytext);
    Lerror += 1;
    //return INT;
}
{HEX}   {
    show_info("HEX");
    uint32_t val = 0;
    sscanf(yytext,"%x", &val);
    printf("val: %u\n", val);
    //return INT;
}
{WRONG_HEX} {
    printf("Error type A at Line %d: Illegal hexadecimal number '%s'\n", yylineno, yytext);
    Lerror += 1;
    //return INT;
}

{FLOAT}     {
    show_info("FLOAT");
    float val = 0;
    sscanf(yytext,"%f", &val);
    printf("val: %f\n", val);
    //return FLOAT;
}
{WRONG_FLOAT}   {
    printf("Error type A at Line %d: Illegal floating point number \'%s\'.\n",yylineno, yytext);
    Lerror += 1;
    //return FLOAT;
}

{SEMI}  {
    show_info("SEMI");
    //return SEMI;
}
{COMMA} {
    show_info("COMMA");
    //return COMMA;
}
{ASSIGNOP} {
   show_info("ASSIGNOP");
    //return ASSIGNOP;
}
{RELOP} {
    show_info("RELOP");
    //return RELOP;
}
{PLUS}  {
    show_info("PLUS");
    //return PLUS;
}
{MINUS} {
    show_info("MINUS");
    //return MINUS;
}
{STAR}  {
    show_info("STAR");
    //return STAR;
}
{DIV}   {
    show_info("DIV");
    //return DIV;
}
{AND}   {
    show_info("AND");
    //return AND;
}
{OR}    {
    show_info("OR");
    //return OR;
}
{DOT}   {
    show_info("DOT");
    //return DOT;
}
{NOT}   {
    show_info("NOT");
    //return NOT;
}
{TYPE}  {
    show_info("TYPE");
    //return TYPE;
}
{LP}    {
    show_info("LP");
    //return LP;
}
{RP}        {
    show_info("RP");
    //return RP;
}
{LB}    {
    show_info("LB");
    //return LB;
}
{RB}    {
    show_info("RB");
    //return RB;
}
{LC}    {
    show_info("LC");
    //return LC;
}
{RC}    {
    show_info("RC");
    //return RC;
}
{STRUCT}    {
    show_info("STRUCT");
    //return STRUCT;
}
{RETURN}    {
    show_info("RETURN");
    //return RETURN;
}
{IF}    {
    show_info("IF");
    //return IF;
}
{ELSE}  {
    show_info("ELSE",yytext);
    //return ELSE;
}
{WHILE}     {
    show_info("WHILE");
    //return WHILE;
}
{ID}    {
    show_info("ID");
    //return ID;
}
{SPACE} {
    show_info("SPACE");
}

"/*"    {
    show_info("COMMENT");
    char cur = input();
    char nxt = input();
    while(cur != '*'  && nxt != '/')
    {
        if(cur == '/' && nxt == '*'){
            printf("Error type B at Line %d: syntax error, \"/*\" \"*/\" not allowed to be nested\n", yylineno);
            break;
        }
        cur = nxt;
        nxt = input();
        if(nxt == '\0'){
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
    Lerror++;
    printf("Error type A at line %d: Mysterious character \"%s\".\n",yylineno,yytext);
}

%%

void show_info(char *str){
    #ifdef  SHOW_INFO
        printf("Line %d: input  %s : %s\n",yylineno, str, yytext);
    #endif
}
