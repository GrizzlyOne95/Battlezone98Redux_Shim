/*
 * Entry: 00416b86
 * Name: NewVector
 * Namespace: Global
 * Signature: VECTOR_3D * NewVector(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl NewVector(lua_State *param_1)

{
  VECTOR_3D *pVVar1;
  lua_State *unaff_ESI;
  
  pVVar1 = lua_newuserdata(unaff_ESI,0xc);
  lua_getfield(unaff_ESI,-10000,"VECTOR_3D");
  lua_setmetatable(unaff_ESI,-2);
  return pVVar1;
}
