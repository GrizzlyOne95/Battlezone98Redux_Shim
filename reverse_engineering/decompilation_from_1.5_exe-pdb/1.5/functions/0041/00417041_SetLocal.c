/*
 * Entry: 00417041
 * Name: SetLocal
 * Namespace: Global
 * Signature: int SetLocal(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetLocal(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = GetHandle(param_1,1);
  SetLocal(iVar1);
  return 0;
}
