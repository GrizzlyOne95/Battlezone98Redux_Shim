/*
 * Entry: 0041bd2c
 * Name: Distance3DSquared
 * Namespace: Global
 * Signature: int Distance3DSquared(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Distance3DSquared(lua_State *param_1)

{
  VECTOR_3D *pVVar1;
  VECTOR_3D *pVVar2;
  undefined4 unaff_EDI;
  float fVar3;
  
  pVVar1 = RequireVector(param_1,1);
  pVVar2 = RequireVector(param_1,2);
  fVar3 = Dist3D_Squared(*pVVar1,*pVVar2);
  lua_pushnumber(param_1,(double)CONCAT44(unaff_EDI,(int)((ulonglong)(double)fVar3 >> 0x20)));
  return 1;
}
