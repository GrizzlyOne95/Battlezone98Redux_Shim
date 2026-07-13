/*
 * Entry: 0041903d
 * Name: CameraFinish
 * Namespace: Global
 * Signature: int CameraFinish(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CameraFinish(lua_State *param_1)

{
  bool bVar1;
  
  bVar1 = CameraFinish();
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
