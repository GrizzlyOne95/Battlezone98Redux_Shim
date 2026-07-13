/*
 * Entry: 005c5b33
 * Name: luaK_getlabel
 * Namespace: Global
 * Signature: int luaK_getlabel(FuncState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaK_getlabel(FuncState *param_1)

{
  param_1->lasttarget = param_1->pc;
  return param_1->pc;
}
