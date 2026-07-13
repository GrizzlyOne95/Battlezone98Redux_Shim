/*
 * Entry: 00418fdd
 * Name: CameraObject
 * Namespace: Global
 * Signature: int CameraObject(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CameraObject(lua_State *param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar2 = GetHandle(param_1,1);
  iVar3 = luaL_checkinteger(param_1,2);
  iVar4 = luaL_checkinteger(param_1,3);
  iVar5 = luaL_checkinteger(param_1,4);
  iVar6 = GetHandle(param_1,5);
  bVar1 = CameraObject(iVar2,iVar3,iVar4,iVar5,iVar6);
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
