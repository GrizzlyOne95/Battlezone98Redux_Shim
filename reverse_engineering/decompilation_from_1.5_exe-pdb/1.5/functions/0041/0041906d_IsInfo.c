/*
 * Entry: 0041906d
 * Name: IsInfo
 * Namespace: Global
 * Signature: int IsInfo(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsInfo(lua_State *param_1)

{
  bool bVar1;
  char *pcVar2;
  
  pcVar2 = luaL_checklstring(param_1,1,(uint *)0x0);
  bVar1 = IsInfo(pcVar2);
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
