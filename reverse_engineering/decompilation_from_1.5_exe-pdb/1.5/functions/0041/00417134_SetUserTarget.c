/*
 * Entry: 00417134
 * Name: SetUserTarget
 * Namespace: Global
 * Signature: int SetUserTarget(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetUserTarget(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = GetHandle(param_1,1);
  SetUserTarget(iVar1);
  return 0;
}
