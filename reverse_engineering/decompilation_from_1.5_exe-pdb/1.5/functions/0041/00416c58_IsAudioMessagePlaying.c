/*
 * Entry: 00416c58
 * Name: IsAudioMessagePlaying
 * Namespace: Global
 * Signature: int IsAudioMessagePlaying(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsAudioMessagePlaying(lua_State *param_1)

{
  bool bVar1;
  
  bVar1 = IsAudioMessagePlaying();
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
