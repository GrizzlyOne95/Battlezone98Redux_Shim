/*
 * Entry: 005c628d
 * Name: luaK_ret
 * Namespace: Global
 * Signature: void luaK_ret(FuncState * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaK_ret(FuncState *param_1,int param_2,int param_3)

{
  luaK_codeABC(param_1,OP_RETURN,param_2,param_3 + 1,0);
  return;
}
