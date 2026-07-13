/*
 * Entry: 00418fc5
 * Name: PanDone
 * Namespace: Global
 * Signature: int PanDone(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl PanDone(lua_State *param_1)

{
  bool bVar1;
  
  bVar1 = PanDone();
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
