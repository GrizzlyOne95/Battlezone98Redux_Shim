/*
 * Entry: 004178b6
 * Name: LockAllies
 * Namespace: Global
 * Signature: int LockAllies(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl LockAllies(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = lua_toboolean(param_1,1);
  LockAllies(iVar1 != 0);
  return 0;
}
