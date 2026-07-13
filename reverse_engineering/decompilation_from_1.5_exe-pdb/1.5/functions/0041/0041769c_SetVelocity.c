/*
 * Entry: 0041769c
 * Name: SetVelocity
 * Namespace: Global
 * Signature: int SetVelocity(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetVelocity(lua_State *param_1)

{
  int iVar1;
  VECTOR_3D *pVVar2;
  
  iVar1 = GetHandle(param_1,1);
  pVVar2 = GetVector(param_1,2);
  if (pVVar2 != (VECTOR_3D *)0x0) {
    SetVelocity(iVar1,pVVar2);
  }
  return 0;
}
