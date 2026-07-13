/*
 * Entry: 00416bb0
 * Name: GetMatrix
 * Namespace: Global
 * Signature: MAT_3D * GetMatrix(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MAT_3D * __cdecl GetMatrix(lua_State *param_1,int param_2)

{
  MAT_3D *pMVar1;
  
  pMVar1 = luaL_testudata(param_1,param_2,"MAT_3D");
  return pMVar1;
}
