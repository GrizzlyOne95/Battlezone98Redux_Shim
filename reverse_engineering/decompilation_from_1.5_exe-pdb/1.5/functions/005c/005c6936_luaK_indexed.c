/*
 * Entry: 005c6936
 * Name: luaK_indexed
 * Namespace: Global
 * Signature: void luaK_indexed(FuncState * param_1, expdesc * param_2, expdesc * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaK_indexed(FuncState *param_1,expdesc *param_2,expdesc *param_3)

{
  int iVar1;
  
  iVar1 = luaK_exp2RK(param_1,param_3);
  (param_2->u).s.aux = iVar1;
  param_2->k = VINDEXED;
  return;
}
