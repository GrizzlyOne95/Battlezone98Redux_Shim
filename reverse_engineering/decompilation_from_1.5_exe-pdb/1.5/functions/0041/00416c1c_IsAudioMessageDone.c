/*
 * Entry: 00416c1c
 * Name: IsAudioMessageDone
 * Namespace: Global
 * Signature: int IsAudioMessageDone(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsAudioMessageDone(lua_State *param_1)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = luaL_checkinteger(param_1,1);
  bVar1 = IsAudioMessageDone(iVar2);
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
