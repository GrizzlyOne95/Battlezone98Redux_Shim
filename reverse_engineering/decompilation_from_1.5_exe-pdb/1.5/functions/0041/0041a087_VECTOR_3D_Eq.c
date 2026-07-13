/*
 * Entry: 0041a087
 * Name: VECTOR_3D_Eq
 * Namespace: Global
 * Signature: int VECTOR_3D_Eq(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl VECTOR_3D_Eq(lua_State *param_1)

{
  VECTOR_3D *pVVar1;
  VECTOR_3D *pVVar2;
  int iVar3;
  
  pVVar1 = RequireVector(param_1,1);
  pVVar2 = RequireVector(param_1,2);
  if (((pVVar2->x == pVVar1->x) && (pVVar2->y == pVVar1->y)) && (pVVar2->z == pVVar1->z)) {
    iVar3 = 1;
  }
  else {
    iVar3 = 0;
  }
  lua_pushboolean(param_1,iVar3);
  return 1;
}
