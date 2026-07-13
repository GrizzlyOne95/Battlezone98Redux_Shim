/*
 * Entry: 0041bb2e
 * Name: DotProduct
 * Namespace: Global
 * Signature: int DotProduct(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl DotProduct(lua_State *param_1)

{
  VECTOR_3D *pVVar1;
  VECTOR_3D *pVVar2;
  undefined4 unaff_EDI;
  
  pVVar1 = RequireVector(param_1,1);
  pVVar2 = RequireVector(param_1,2);
  lua_pushnumber(param_1,(double)CONCAT44(unaff_EDI,
                                          (int)((ulonglong)
                                                (double)(pVVar2->x * pVVar1->x +
                                                        pVVar2->y * pVVar1->y +
                                                        pVVar2->z * pVVar1->z) >> 0x20)));
  return 1;
}
