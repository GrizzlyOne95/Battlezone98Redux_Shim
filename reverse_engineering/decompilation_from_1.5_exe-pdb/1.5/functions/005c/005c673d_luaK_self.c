/*
 * Entry: 005c673d
 * Name: luaK_self
 * Namespace: Global
 * Signature: void luaK_self(FuncState * param_1, expdesc * param_2, expdesc * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaK_self(FuncState *param_1,expdesc *param_2,expdesc *param_3)

{
  int iVar1;
  int iVar2;
  FuncState *pFVar3;
  
  pFVar3 = param_1;
  luaK_exp2anyreg(param_1,param_2);
  freeexp(param_1,(expdesc *)pFVar3);
  iVar1 = param_1->freereg;
  luaK_reserveregs(param_1,2);
  iVar2 = luaK_exp2RK(param_1,param_3);
  pFVar3 = param_1;
  luaK_codeABC(param_1,OP_SELF,iVar1,(param_2->u).s.info,iVar2);
  freeexp(param_1,(expdesc *)pFVar3);
  (param_2->u).s.info = iVar1;
  param_2->k = VNONRELOC;
  return;
}
