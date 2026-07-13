/*
 * Entry: 005c6c9b
 * Name: luaK_patchlist
 * Namespace: Global
 * Signature: void luaK_patchlist(FuncState * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaK_patchlist(FuncState *param_1,int param_2,int param_3)

{
  int unaff_retaddr;
  
  if (param_3 == param_1->pc) {
    luaK_patchtohere(param_1,param_2);
    return;
  }
  patchlistaux((FuncState *)param_3,0xff,param_3,unaff_retaddr,(int)param_1);
  return;
}
