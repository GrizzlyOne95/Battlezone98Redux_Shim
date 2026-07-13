/*
 * Entry: 0041a455
 * Name: MAT_3D_Mul
 * Namespace: Global
 * Signature: int MAT_3D_Mul(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl MAT_3D_Mul(lua_State *param_1)

{
  MAT_3D *pMVar1;
  MAT_3D *pMVar2;
  lua_State *plVar3;
  VECTOR_3D *pVVar4;
  int iVar5;
  float *pfVar6;
  lua_State *unaff_EDI;
  long lVar7;
  MAT_3D local_84;
  float local_44 [16];
  
  pMVar1 = GetMatrix(param_1,1);
  if (pMVar1 != (MAT_3D *)0x0) {
    pMVar2 = GetMatrix(param_1,2);
    if (pMVar2 != (MAT_3D *)0x0) {
      pMVar1 = Matrix_Multiply(&local_84,pMVar1,pMVar2);
      pfVar6 = local_44;
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        *pfVar6 = pMVar1->right_x;
        pMVar1 = (MAT_3D *)&pMVar1->right_y;
        pfVar6 = pfVar6 + 1;
      }
      pMVar1 = NewMatrix(unaff_EDI);
      pfVar6 = local_44;
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        pMVar1->right_x = *pfVar6;
        pfVar6 = pfVar6 + 1;
        pMVar1 = (MAT_3D *)&pMVar1->right_y;
      }
      return 1;
    }
    plVar3 = (lua_State *)GetVector(param_1,2);
    if (plVar3 != (lua_State *)0x0) {
      lVar7 = 1;
      pVVar4 = NewVector(plVar3);
      Vector_Transform(pVVar4,(VECTOR_3D *)plVar3,lVar7,pMVar1);
      return 1;
    }
  }
  return 0;
}
