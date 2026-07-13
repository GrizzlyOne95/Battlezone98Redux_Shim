/*
 * Entry: 005c2e84
 * Name: luaB_pcall
 * Namespace: Global
 * Signature: int luaB_pcall(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_pcall(lua_State *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  luaL_checkany(param_1,1);
  iVar3 = 0;
  iVar2 = -1;
  iVar1 = lua_gettop(param_1);
  iVar1 = lua_pcall(param_1,iVar1 + -1,iVar2,iVar3);
  lua_pushboolean(param_1,(uint)(iVar1 == 0));
  lua_insert(param_1,1);
  iVar1 = lua_gettop(param_1);
  return iVar1;
}
