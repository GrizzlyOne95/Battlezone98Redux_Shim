/*
 * Entry: 0045ec6a
 * Name: BuildObject
 * Namespace: Global
 * Signature: int BuildObject(char * param_1, int param_2, VECTOR_3D * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl BuildObject(char *param_1,int param_2,VECTOR_3D *param_3)

{
  float fVar1;
  int iVar2;
  MAT_3D *pMVar3;
  MAT_3D *pMVar4;
  MAT_3D local_44;
  
  fVar1 = param_3->x;
  pMVar3 = &Identity_Matrix;
  pMVar4 = &local_44;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    pMVar4->right_x = pMVar3->right_x;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
    pMVar4 = (MAT_3D *)&pMVar4->right_y;
  }
  local_44.posit_x = (double)fVar1;
  local_44.posit_y = (double)param_3->y;
  local_44.posit_z = (double)param_3->z;
  iVar2 = BuildObject(param_1,param_2,&local_44);
  return iVar2;
}
