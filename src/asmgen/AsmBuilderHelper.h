#ifndef __OLIVE_HEADER_INCLUDED__
#define __OLIVE_HEADER_INCLUDED__
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "codegen/asm/AsmBuilder.h"
#define DEBUG_TYPE "remniw-AsmBuilderHelper"
#define BRG_UNDEF 0
#define BRG_CONST 1
#define BRG_LABEL 2
#define BRG_REG 3
#define BRG_CALLARGS 4
#define BRG_FUNCARG 5
#define BRG_RET 6
#define BRG_BR 7
#define BRG_SWITCH 8
#define BRG_INDIRECTBR 9
#define BRG_INVOKE 10
#define BRG_RESUME 11
#define BRG_UNREACHABLE 12
#define BRG_CLEANUPRET 13
#define BRG_CATCHRET 14
#define BRG_CATCHSWITCH 15
#define BRG_CALLBR 16
#define BRG_FNEG 17
#define BRG_ADD 18
#define BRG_FADD 19
#define BRG_SUB 20
#define BRG_FSUB 21
#define BRG_MUL 22
#define BRG_FMUL 23
#define BRG_UDIV 24
#define BRG_SDIV 25
#define BRG_FDIV 26
#define BRG_UREM 27
#define BRG_SREM 28
#define BRG_FREM 29
#define BRG_SHL 30
#define BRG_LSHR 31
#define BRG_ASHR 32
#define BRG_AND 33
#define BRG_OR 34
#define BRG_XOR 35
#define BRG_ALLOCA 36
#define BRG_LOAD 37
#define BRG_STORE 38
#define BRG_GETELEMENTPTR 39
#define BRG_FENCE 40
#define BRG_ATOMICCMPXCHG 41
#define BRG_ATOMICRMW 42
#define BRG_TRUNC 43
#define BRG_ZEXT 44
#define BRG_SEXT 45
#define BRG_FPTOUI 46
#define BRG_FPTOSI 47
#define BRG_UITOFP 48
#define BRG_SITOFP 49
#define BRG_FPTRUNC 50
#define BRG_FPEXT 51
#define BRG_PTRTOINT 52
#define BRG_INTTOPTR 53
#define BRG_BITCAST 54
#define BRG_ADDRSPACECAST 55
#define BRG_CLEANUPPAD 56
#define BRG_CATCHPAD 57
#define BRG_ICMP 58
#define BRG_FCMP 59
#define BRG_PHI 60
#define BRG_CALL 61
#define BRG_SELECT 62
#define BRG_USEROP1 63
#define BRG_USEROP2 64
#define BRG_VAARG 65
#define BRG_EXTRACTELEMENT 66
#define BRG_INSERTELEMENT 67
#define BRG_SHUFFLEVECTOR 68
#define BRG_EXTRACTVALUE 69
#define BRG_INSERTVALUE 70
#define BRG_LANDINGPAD 71
#define BRG_FREEZE 72

struct burm_state {
  int op;
  NODEPTR node;
  struct burm_state **kids;
  COST cost[10];
  struct {
    unsigned burm_stmt:4;
    unsigned burm_reg:5;
    unsigned burm_imm:1;
    unsigned burm_mem:3;
    unsigned burm_label:1;
    unsigned burm_cond:2;
    unsigned burm_call_arg:3;
    unsigned burm_call_args:2;
    unsigned burm_func_arg:1;
  } rule;
};


struct burm_state *burm_label(NODEPTR);
struct burm_state *burm_label1(NODEPTR);

void dumpCover(NODEPTR,int,int);

#endif
