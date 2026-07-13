/*
 * Entry: 00416f36
 * Name: IsAlive
 * Namespace: Global
 * Signature: int IsAlive(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsAlive(lua_State *param_1)

{
  bool bVar1;
  int local_8;
  
  local_8 = GetHandle(param_1,1);
  bVar1 = IsAlive(&local_8);
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
