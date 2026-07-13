/*
 * Entry: 004190ac
 * Name: IsHosting
 * Namespace: Global
 * Signature: int IsHosting(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsHosting(lua_State *param_1)

{
  bool bVar1;
  
  bVar1 = Net::GetHosting();
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
