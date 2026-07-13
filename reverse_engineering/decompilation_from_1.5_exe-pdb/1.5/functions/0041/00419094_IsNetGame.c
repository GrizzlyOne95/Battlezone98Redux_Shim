/*
 * Entry: 00419094
 * Name: IsNetGame
 * Namespace: Global
 * Signature: int IsNetGame(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsNetGame(lua_State *param_1)

{
  bool bVar1;
  
  bVar1 = Net::IsNetGame();
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
