/*
 * Entry: 00418f84
 * Name: CameraPathDir
 * Namespace: Global
 * Signature: int CameraPathDir(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CameraPathDir(lua_State *param_1)

{
  bool bVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  
  pcVar2 = luaL_checklstring(param_1,1,(uint *)0x0);
  iVar3 = luaL_checkinteger(param_1,2);
  iVar4 = luaL_checkinteger(param_1,3);
  bVar1 = CameraPathDir(pcVar2,iVar3,iVar4);
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
