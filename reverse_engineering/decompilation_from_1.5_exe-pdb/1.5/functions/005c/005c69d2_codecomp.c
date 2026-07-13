/*
 * Entry: 005c69d2
 * Name: codecomp
 * Namespace: Global
 * Signature: void codecomp(FuncState * param_1, OpCode param_2, int param_3, expdesc * param_4, expdesc * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
codecomp(FuncState *param_1,OpCode param_2,int param_3,expdesc *param_4,expdesc *param_5)

{
  int iVar1;
  int iVar2;
  int extraout_EDX;
  expdesc *unaff_ESI;
  FuncState *unaff_EDI;
  FuncState *pFVar3;
  FuncState *pFVar4;
  
  iVar1 = luaK_exp2RK(unaff_EDI,unaff_ESI);
  pFVar4 = unaff_EDI;
  luaK_exp2RK(unaff_EDI,(expdesc *)param_3);
  pFVar3 = unaff_EDI;
  freeexp(unaff_EDI,(expdesc *)pFVar4);
  freeexp(unaff_EDI,(expdesc *)pFVar3);
  iVar2 = extraout_EDX;
  if ((param_2 == OP_MOVE) && (iVar2 = extraout_EDX, param_1 != (FuncState *)0x17)) {
    param_2 = OP_LOADK;
    iVar2 = iVar1;
    iVar1 = extraout_EDX;
  }
  iVar2 = condjump(unaff_EDI,(OpCode)param_1,param_2,iVar1,iVar2);
  (unaff_ESI->u).s.info = iVar2;
  unaff_ESI->k = VJMP;
  return;
}
