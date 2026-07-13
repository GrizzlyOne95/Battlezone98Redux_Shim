/*
 * Entry: 0041bb6f
 * Name: CrossProduct
 * Namespace: Global
 * Signature: int CrossProduct(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CrossProduct(lua_State *param_1)

{
  VECTOR_3D *pVVar1;
  VECTOR_3D *pVVar2;
  lua_State *unaff_EDI;
  VECTOR_3D local_1c;
  float local_10;
  float fStack_c;
  float fStack_8;
  
  pVVar1 = RequireVector(param_1,1);
  pVVar2 = RequireVector(param_1,2);
  pVVar1 = Cross_Product(&local_1c,pVVar1,pVVar2);
  local_10 = pVVar1->x;
  fStack_c = pVVar1->y;
  fStack_8 = pVVar1->z;
  pVVar1 = NewVector(unaff_EDI);
  pVVar1->x = local_10;
  pVVar1->y = fStack_c;
  pVVar1->z = fStack_8;
  return 1;
}
