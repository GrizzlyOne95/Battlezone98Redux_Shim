/*
 * Entry: 0041bc5e
 * Name: Distance2D
 * Namespace: Global
 * Signature: int Distance2D(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Distance2D(lua_State *param_1)

{
  float fVar1;
  float fVar2;
  VECTOR_3D *pVVar3;
  VECTOR_3D *pVVar4;
  undefined4 unaff_EDI;
  
  pVVar3 = RequireVector(param_1,1);
  pVVar4 = RequireVector(param_1,2);
  fVar1 = pVVar3->x - pVVar4->x;
  fVar2 = pVVar3->z - pVVar4->z;
  lua_pushnumber(param_1,(double)CONCAT44(unaff_EDI,
                                          (int)((ulonglong)
                                                (double)SQRT(fVar2 * fVar2 + fVar1 * fVar1) >> 0x20)
                                         ));
  return 1;
}
