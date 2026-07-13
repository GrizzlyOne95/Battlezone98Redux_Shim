/*
 * Entry: 005c6071
 * Name: luaK_fixline
 * Namespace: Global
 * Signature: void luaK_fixline(FuncState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaK_fixline(FuncState *param_1,int param_2)

{
  param_1->f->lineinfo[param_1->pc + -1] = param_2;
  return;
}
