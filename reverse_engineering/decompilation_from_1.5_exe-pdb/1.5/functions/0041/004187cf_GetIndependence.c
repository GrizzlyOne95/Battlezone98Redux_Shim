/*
 * Entry: 004187cf
 * Name: GetIndependence
 * Namespace: Global
 * Signature: int GetIndependence(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetIndependence(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = GetHandle(param_1,1);
  iVar1 = GetIndependence(iVar1);
  lua_pushinteger(param_1,iVar1);
  return 1;
}
