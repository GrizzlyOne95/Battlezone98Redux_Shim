/*
 * Entry: 005c6566
 * Name: luaK_exp2nextreg
 * Namespace: Global
 * Signature: void luaK_exp2nextreg(FuncState * param_1, expdesc * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaK_exp2nextreg(FuncState *param_1,expdesc *param_2)

{
  FuncState *pFVar1;
  int iVar2;
  
  pFVar1 = param_1;
  luaK_dischargevars(param_1,param_2);
  freeexp(param_1,(expdesc *)pFVar1);
  iVar2 = 1;
  pFVar1 = param_1;
  luaK_reserveregs(param_1,1);
  exp2reg((FuncState *)(param_1->freereg + -1),(expdesc *)pFVar1,iVar2);
  return;
}
