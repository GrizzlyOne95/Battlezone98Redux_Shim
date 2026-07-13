/*
 * Entry: 00418b9b
 * Name: Build
 * Namespace: Global
 * Signature: int Build(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Build(lua_State *param_1)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  
  iVar1 = GetHandle(param_1,1);
  pcVar2 = luaL_checklstring(param_1,2,(uint *)0x0);
  iVar3 = luaL_optinteger(param_1,3,1);
  Build(iVar1,pcVar2,iVar3);
  return 0;
}
