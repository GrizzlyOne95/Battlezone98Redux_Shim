/*
 * Entry: 00418cc3
 * Name: HopOut
 * Namespace: Global
 * Signature: int HopOut(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl HopOut(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = GetHandle(param_1,1);
  HopOut(iVar1);
  return 0;
}
