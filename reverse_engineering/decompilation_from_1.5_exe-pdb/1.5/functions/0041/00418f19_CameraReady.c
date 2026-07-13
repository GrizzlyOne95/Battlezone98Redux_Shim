/*
 * Entry: 00418f19
 * Name: CameraReady
 * Namespace: Global
 * Signature: int CameraReady(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CameraReady(lua_State *param_1)

{
  bool bVar1;
  
  bVar1 = CameraReady();
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
