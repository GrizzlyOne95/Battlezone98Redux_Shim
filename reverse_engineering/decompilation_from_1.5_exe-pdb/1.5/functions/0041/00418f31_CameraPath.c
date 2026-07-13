/*
 * Entry: 00418f31
 * Name: CameraPath
 * Namespace: Global
 * Signature: int CameraPath(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CameraPath(lua_State *param_1)

{
  bool bVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  pcVar2 = luaL_checklstring(param_1,1,(uint *)0x0);
  iVar3 = luaL_checkinteger(param_1,2);
  iVar4 = luaL_checkinteger(param_1,3);
  iVar5 = GetHandle(param_1,4);
  bVar1 = CameraPath(pcVar2,iVar3,iVar4,iVar5);
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
