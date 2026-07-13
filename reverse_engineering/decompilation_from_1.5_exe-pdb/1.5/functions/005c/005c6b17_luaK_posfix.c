/*
 * Entry: 005c6b17
 * Name: luaK_posfix
 * Namespace: Global
 * Signature: void luaK_posfix(FuncState * param_1, BinOpr param_2, expdesc * param_3, expdesc * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaK_posfix(FuncState *param_1,BinOpr param_2,expdesc *param_3,expdesc *param_4)

{
  uint *puVar1;
  int *piVar2;
  int iVar3;
  undefined4 *extraout_EDX;
  expdesc *unaff_ESI;
  expdesc *unaff_EDI;
  FuncState *pFVar4;
  OpCode OVar5;
  expdesc *peVar6;
  
  switch(param_2) {
  case OPR_ADD:
    pFVar4 = (FuncState *)&DAT_0000000c;
    break;
  case OPR_SUB:
    pFVar4 = (FuncState *)0xd;
    break;
  case OPR_MUL:
    pFVar4 = (FuncState *)0xe;
    break;
  case OPR_DIV:
    pFVar4 = (FuncState *)0xf;
    break;
  case OPR_MOD:
    pFVar4 = (FuncState *)0x10;
    break;
  case OPR_POW:
    pFVar4 = (FuncState *)0x11;
    break;
  case OPR_CONCAT:
    luaK_exp2val(param_1,param_4);
    if ((param_4->k == VRELOCABLE) && (((byte)param_1->f->code[(param_4->u).s.info] & 0x3f) == 0x15)
       ) {
      freeexp(param_1,unaff_EDI);
      puVar1 = param_1->f->code + (param_4->u).s.info;
      *puVar1 = extraout_EDX[2] << 0x17 | *puVar1 & 0x7fffff;
      *extraout_EDX = 0xb;
      extraout_EDX[2] = (param_4->u).s.info;
      return;
    }
    peVar6 = param_4;
    luaK_exp2nextreg(param_1,param_4);
    codearith((FuncState *)0x15,(OpCode)param_4,(expdesc *)param_1,peVar6);
    return;
  case OPR_NE:
    OVar5 = OP_MOVE;
    goto LAB_005c6c24;
  case OPR_EQ:
    OVar5 = OP_LOADK;
LAB_005c6c24:
    pFVar4 = (FuncState *)0x17;
LAB_005c6c4d:
    codecomp(pFVar4,OVar5,(int)param_4,unaff_EDI,unaff_ESI);
    return;
  case OPR_LT:
    OVar5 = OP_LOADK;
    goto LAB_005c6c34;
  case OPR_LE:
    OVar5 = OP_LOADK;
    goto LAB_005c6c4b;
  case OPR_GT:
    OVar5 = OP_MOVE;
LAB_005c6c34:
    pFVar4 = (FuncState *)0x18;
    goto LAB_005c6c4d;
  case OPR_GE:
    OVar5 = OP_MOVE;
LAB_005c6c4b:
    pFVar4 = (FuncState *)0x19;
    goto LAB_005c6c4d;
  case OPR_AND:
    luaK_dischargevars(param_1,param_4);
    iVar3 = param_3->f;
    piVar2 = &param_4->f;
    goto LAB_005c6b5b;
  case OPR_OR:
    luaK_dischargevars(param_1,param_4);
    iVar3 = param_3->t;
    piVar2 = &param_4->t;
LAB_005c6b5b:
    luaK_concat(param_1,piVar2,iVar3);
    for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
      param_3->k = param_4->k;
      param_4 = (expdesc *)&param_4->field_0x4;
      param_3 = (expdesc *)&param_3->field_0x4;
    }
  default:
    goto switchD_005c6b28_default;
  }
  codearith(pFVar4,(OpCode)param_4,unaff_EDI,unaff_ESI);
switchD_005c6b28_default:
  return;
}
