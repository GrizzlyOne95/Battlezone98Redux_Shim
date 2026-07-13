/*
 * Entry: 0041bbf8
 * Name: Length
 * Namespace: Global
 * Signature: int Length(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Length(lua_State *param_1)

{
  VECTOR_3D *pVVar1;
  undefined4 unaff_EDI;
  float fVar2;
  
  pVVar1 = RequireVector(param_1,1);
  fVar2 = VecLen(*pVVar1);
  lua_pushnumber(param_1,(double)CONCAT44(unaff_EDI,(int)((ulonglong)(double)fVar2 >> 0x20)));
  return 1;
}
