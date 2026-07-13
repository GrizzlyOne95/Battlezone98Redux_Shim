/*
 * Entry: 00419055
 * Name: CameraCancelled
 * Namespace: Global
 * Signature: int CameraCancelled(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CameraCancelled(lua_State *param_1)

{
  bool bVar1;
  
  bVar1 = CameraCancelled();
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
