/*
 * Entry: 00416c70
 * Name: GetHandle
 * Namespace: Global
 * Signature: int GetHandle(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetHandle(lua_State *param_1)

{
  char *pcVar1;
  int iVar2;
  
  pcVar1 = luaL_checklstring(param_1,1,(uint *)0x0);
  iVar2 = GetHandle(pcVar1);
  PushHandle(param_1,iVar2);
  return 1;
}
