/*
 * Entry: 005c6793
 * Name: jumponcond
 * Namespace: Global
 * Signature: int jumponcond(FuncState * param_1, expdesc * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl jumponcond(FuncState *param_1,expdesc *param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  FuncState *unaff_ESI;
  int *unaff_EDI;
  FuncState *unaff_retaddr;
  
  if ((*unaff_EDI == 0xb) &&
     (uVar1 = unaff_ESI->f->code[unaff_EDI[2]], ((byte)uVar1 & 0x3f) == 0x13)) {
    unaff_ESI->pc = unaff_ESI->pc + -1;
    iVar2 = condjump(unaff_ESI,OP_TEST,uVar1 >> 0x17,0,(uint)(param_1 == (FuncState *)0x0));
    return iVar2;
  }
  discharge2anyreg(unaff_retaddr,(expdesc *)param_1);
  freeexp(unaff_ESI,(expdesc *)unaff_retaddr);
  iVar2 = condjump(unaff_ESI,OP_TESTSET,0xff,unaff_EDI[2],(int)param_1);
  return iVar2;
}
