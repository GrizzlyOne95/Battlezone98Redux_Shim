/*
 * Entry: 00416b5a
 * Name: GetVector
 * Namespace: Global
 * Signature: VECTOR_3D * GetVector(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl GetVector(lua_State *param_1,int param_2)

{
  VECTOR_3D *pVVar1;
  
  pVVar1 = luaL_testudata(param_1,param_2,"VECTOR_3D");
  return pVVar1;
}
