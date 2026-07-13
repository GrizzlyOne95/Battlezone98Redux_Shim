/*
 * Entry: 00417620
 * Name: GetFront
 * Namespace: Global
 * Signature: int GetFront(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetFront(lua_State *param_1)

{
  int iVar1;
  VECTOR_3D *pVVar2;
  lua_State *unaff_EDI;
  VECTOR_3D local_1c;
  float local_10;
  float fStack_c;
  float fStack_8;
  
  iVar1 = GetHandle(param_1,1);
  pVVar2 = GetFront(&local_1c,iVar1);
  local_10 = pVVar2->x;
  fStack_c = pVVar2->y;
  fStack_8 = pVVar2->z;
  pVVar2 = NewVector(unaff_EDI);
  pVVar2->x = local_10;
  pVVar2->y = fStack_c;
  pVVar2->z = fStack_8;
  return 1;
}
