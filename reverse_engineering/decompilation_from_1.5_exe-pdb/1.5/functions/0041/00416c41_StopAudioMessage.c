/*
 * Entry: 00416c41
 * Name: StopAudioMessage
 * Namespace: Global
 * Signature: int StopAudioMessage(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl StopAudioMessage(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = luaL_checkinteger(param_1,1);
  StopAudioMessage(iVar1);
  return 0;
}
