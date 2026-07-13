/*
 * Entry: 00416bf8
 * Name: AudioMessage
 * Namespace: Global
 * Signature: int AudioMessage(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AudioMessage(lua_State *param_1)

{
  char *pcVar1;
  int iVar2;
  
  pcVar1 = luaL_checklstring(param_1,1,(uint *)0x0);
  iVar2 = AudioMessage(pcVar1);
  lua_pushinteger(param_1,iVar2);
  return 1;
}
