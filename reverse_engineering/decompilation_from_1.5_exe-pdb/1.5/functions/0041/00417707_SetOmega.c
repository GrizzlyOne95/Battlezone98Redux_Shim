/*
 * Entry: 00417707
 * Name: SetOmega
 * Namespace: Global
 * Signature: int SetOmega(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetOmega(lua_State *param_1)

{
  int iVar1;
  VECTOR_3D *pVVar2;
  
  iVar1 = GetHandle(param_1,1);
  pVVar2 = GetVector(param_1,2);
  if (pVVar2 != (VECTOR_3D *)0x0) {
    SetOmega(iVar1,pVVar2);
  }
  return 0;
}
