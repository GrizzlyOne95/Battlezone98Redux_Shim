/*
 * Entry: 00416f08
 * Name: IsValid
 * Namespace: Global
 * Signature: int IsValid(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsValid(lua_State *param_1)

{
  bool bVar1;
  int local_8;
  
  local_8 = GetHandle(param_1,1);
  bVar1 = IsValid(&local_8);
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
