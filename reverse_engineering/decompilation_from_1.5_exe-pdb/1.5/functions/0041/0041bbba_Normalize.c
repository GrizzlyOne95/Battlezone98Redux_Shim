/*
 * Entry: 0041bbba
 * Name: Normalize
 * Namespace: Global
 * Signature: int Normalize(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Normalize(lua_State *param_1)

{
  VECTOR_3D *pVVar1;
  lua_State *unaff_EDI;
  VECTOR_3D local_1c;
  float local_10;
  float fStack_c;
  float fStack_8;
  
  pVVar1 = RequireVector(param_1,1);
  pVVar1 = Normalize_Vector(&local_1c,pVVar1);
  local_10 = pVVar1->x;
  fStack_c = pVVar1->y;
  fStack_8 = pVVar1->z;
  pVVar1 = NewVector(unaff_EDI);
  pVVar1->x = local_10;
  pVVar1->y = fStack_c;
  pVVar1->z = fStack_8;
  return 1;
}
