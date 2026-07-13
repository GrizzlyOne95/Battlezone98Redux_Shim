/*
 * Entry: 004174d6
 * Name: GetTransform
 * Namespace: Global
 * Signature: int GetTransform(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetTransform(lua_State *param_1)

{
  int iVar1;
  MAT_3D *pMVar2;
  float *pfVar3;
  lua_State *unaff_EDI;
  MAT_3D local_84;
  float local_44 [16];
  
  iVar1 = GetHandle(param_1,1);
  pMVar2 = GetTransform(&local_84,iVar1);
  pfVar3 = local_44;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pfVar3 = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pfVar3 = pfVar3 + 1;
  }
  pMVar2 = NewMatrix(unaff_EDI);
  pfVar3 = local_44;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    pMVar2->right_x = *pfVar3;
    pfVar3 = pfVar3 + 1;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
  }
  return 1;
}
