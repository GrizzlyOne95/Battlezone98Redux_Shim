/*
 * Entry: 00416bc6
 * Name: NewMatrix
 * Namespace: Global
 * Signature: MAT_3D * NewMatrix(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MAT_3D * __cdecl NewMatrix(lua_State *param_1)

{
  MAT_3D *pMVar1;
  lua_State *unaff_ESI;
  
  pMVar1 = lua_newuserdata(unaff_ESI,0x40);
  lua_getfield(unaff_ESI,-10000,"MAT_3D");
  lua_setmetatable(unaff_ESI,-2);
  return pMVar1;
}
