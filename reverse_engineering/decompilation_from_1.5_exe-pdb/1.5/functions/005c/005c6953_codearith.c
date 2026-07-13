/*
 * Entry: 005c6953
 * Name: codearith
 * Namespace: Global
 * Signature: void codearith(FuncState * param_1, OpCode param_2, expdesc * param_3, expdesc * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl codearith(FuncState *param_1,OpCode param_2,expdesc *param_3,expdesc *param_4)

{
  expdesc *in_EAX;
  int iVar1;
  int iVar2;
  int extraout_EDX;
  expdesc *unaff_EBX;
  expdesc *unaff_EBP;
  expdesc *unaff_ESI;
  FuncState *unaff_EDI;
  FuncState *pFVar3;
  
  iVar1 = constfolding((OpCode)param_1,unaff_ESI,unaff_EBP);
  if (iVar1 == 0) {
    if ((param_1 == (FuncState *)0x12) || (param_1 == (FuncState *)0x14)) {
      iVar1 = 0;
    }
    else {
      iVar1 = luaK_exp2RK(unaff_EDI,(expdesc *)param_2);
    }
    iVar2 = luaK_exp2RK(unaff_EDI,in_EAX);
    pFVar3 = unaff_EDI;
    if (iVar1 < iVar2) {
      freeexp(unaff_EDI,unaff_EBX);
    }
    else {
      freeexp(unaff_EDI,unaff_EBX);
    }
    freeexp(unaff_EDI,(expdesc *)pFVar3);
    iVar1 = luaK_codeABC(unaff_EDI,(OpCode)param_1,0,extraout_EDX,iVar1);
    (in_EAX->u).s.info = iVar1;
    in_EAX->k = VRELOCABLE;
  }
  return;
}
