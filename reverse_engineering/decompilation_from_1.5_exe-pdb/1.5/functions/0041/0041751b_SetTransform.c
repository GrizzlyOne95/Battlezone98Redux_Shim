/*
 * Entry: 0041751b
 * Name: SetTransform
 * Namespace: Global
 * Signature: int SetTransform(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetTransform(lua_State *param_1)

{
  int iVar1;
  MAT_3D *pMVar2;
  
  iVar1 = GetHandle(param_1,1);
  pMVar2 = GetMatrix(param_1,2);
  if (pMVar2 != (MAT_3D *)0x0) {
    SetTransform(iVar1,pMVar2);
  }
  return 0;
}
