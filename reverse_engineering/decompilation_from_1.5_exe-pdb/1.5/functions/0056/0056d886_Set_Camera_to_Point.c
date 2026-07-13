/*
 * Entry: 0056d886
 * Name: Set_Camera_to_Point
 * Namespace: Global
 * Signature: void Set_Camera_to_Point(float param_1, float param_2, float param_3, VECTOR_3D * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Set_Camera_to_Point(float param_1,float param_2,float param_3,VECTOR_3D *param_4)

{
  MAT_3D *pMVar1;
  float *in_ECX;
  int iVar2;
  VECTOR_3D *unaff_ESI;
  VECTOR_3D *unaff_EDI;
  MAT_3D *pMVar3;
  MAT_3D local_90;
  MAT_3D local_50;
  float local_10;
  float local_c;
  float local_8;
  
  local_10 = param_1 - *in_ECX;
  local_c = param_2 - in_ECX[1];
  local_8 = param_3 - in_ECX[2];
  pMVar1 = Build_Directinal_Matrix(&local_90,unaff_EDI,unaff_ESI);
  pMVar3 = &local_50;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    pMVar3->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
  }
  Camera_Set_Matrix(&View_Record.MainCam,&local_50);
  return;
}
