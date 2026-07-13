/*
 * Entry: 00416b70
 * Name: RequireVector
 * Namespace: Global
 * Signature: VECTOR_3D * RequireVector(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl RequireVector(lua_State *param_1,int param_2)

{
  VECTOR_3D *pVVar1;
  
  pVVar1 = luaL_checkudata(param_1,param_2,"VECTOR_3D");
  return pVVar1;
}
