/*
 * Entry: 0041bc28
 * Name: LengthSquared
 * Namespace: Global
 * Signature: int LengthSquared(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl LengthSquared(lua_State *param_1)

{
  VECTOR_3D *pVVar1;
  undefined4 unaff_retaddr;
  
  pVVar1 = RequireVector(param_1,1);
  lua_pushnumber(param_1,(double)CONCAT44(unaff_retaddr,
                                          (int)((ulonglong)
                                                (double)(pVVar1->x * pVVar1->x +
                                                         pVVar1->y * pVVar1->y +
                                                        pVVar1->z * pVVar1->z) >> 0x20)));
  return 1;
}
