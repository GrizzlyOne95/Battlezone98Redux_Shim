/*
 * Entry: 005c5e17
 * Name: luaK_stringK
 * Namespace: Global
 * Signature: int luaK_stringK(FuncState * param_1, TString * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaK_stringK(FuncState *param_1,TString *param_2)

{
  int iVar1;
  
  iVar1 = addk((FuncState *)&stack0xffffffec,(lua_TValue *)&stack0xffffffec,
               (lua_TValue *)&param_2->tsv);
  return iVar1;
}
