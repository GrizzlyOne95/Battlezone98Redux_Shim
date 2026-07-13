/*
 * Entry: 005c5d03
 * Name: luaK_reserveregs
 * Namespace: Global
 * Signature: void luaK_reserveregs(FuncState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaK_reserveregs(FuncState *param_1,int param_2)

{
  luaK_checkstack(param_1,param_2);
  param_1->freereg = param_1->freereg + param_2;
  return;
}
