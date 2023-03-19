#ifndef _OBJCODE_H
#define _OBJCODE_H
#include "intercode.h"

typedef struct VarOffset_ *VarOffset;
typedef struct Register
{
    bool used;          // 是否使用
    char *name;         // 寄存器名字
    VarOffset variable; // 所存变量的偏移值：用于save到原地址
} Register;

typedef struct VarOffset_
{
    char name[32]; // 变量名字
    int reg;       // 寄存器号
    int offset;    // 偏移量
    VarOffset next;
} VarOffset_;

/* 初始化所有寄存器 */
void initRegisters();
/* 寻找合适寄存器并填入操作内容 */
int findRegisters(Operand op, FILE *file);
/* 将寄存器值存回原地址 */
void SaveRegister(int index, FILE *file);
/* 获取操作数偏移量 */
VarOffset getVarOffset(Operand op);
/* 创建操作数偏移量 */
void createVarOffset(Operand op);

/* 目标代码生成 */
void generateObjectCode(FILE *file);
void generateLableObjectCode(InterCodeList curInterCodeList, FILE *file);
void generateFuncObjectCode(InterCodeList curInterCodeList, FILE *file);
void generateAssignObjectCode(InterCodeList curInterCodeList, FILE *file);
void generateArithmeticCode(char *opType, InterCodeList curInterCodeList, FILE *file);
void generateAddObjectCode(InterCodeList curInterCodeList, FILE *file);
void generateSubObjectCode(InterCodeList curInterCodeList, FILE *file);
void generateMulObjectCode(InterCodeList curInterCodeList, FILE *file);
void generateDivObjectCode(InterCodeList curInterCodeList, FILE *file);
void generateGetAddrObjectCode(InterCodeList curInterCodeList, FILE *file);
void generateGetContentObjectCode(InterCodeList curInterCodeList, FILE *file);
void generateToAddrObjectCode(InterCodeList curInterCodeList, FILE *file);
void generateGotoObjectCode(InterCodeList curInterCodeList, FILE *file);
void generateIfgotoObjectCode(InterCodeList curInterCodeList, FILE *file);
void generateReturnObjectCode(InterCodeList curInterCodeList, FILE *file);
void generateDecObjectCode(InterCodeList curInterCodeList, FILE *file);
void generateArgObjectCode(InterCodeList curInterCodeList, FILE *file);
void generateCallObjectCode(InterCodeList curInterCodeList, FILE *file);
void generateParamObjectCode(InterCodeList curInterCodeList, FILE *file);
void generateReadObjectCode(InterCodeList curInterCodeList, FILE *file);
void generateWriteObjectCode(InterCodeList curInterCodeList, FILE *file);
#endif