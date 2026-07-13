/*
 * Entry: 005c62cc
 * Name: luaK_patchtohere
 * Namespace: Global
 * Signature: void luaK_patchtohere(FuncState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaK_patchtohere(FuncState *param_1,int param_2)

{
  param_1->lasttarget = param_1->pc;
  luaK_concat(param_1,&param_1->jpc,param_2);
  return;
}
