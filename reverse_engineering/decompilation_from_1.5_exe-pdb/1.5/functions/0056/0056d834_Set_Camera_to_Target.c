/*
 * Entry: 0056d834
 * Name: Set_Camera_to_Target
 * Namespace: Global
 * Signature: void Set_Camera_to_Target(_OBJ76 * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Set_Camera_to_Target(_OBJ76 *param_1,VECTOR_3D *param_2)

{
  int in_EAX;
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
  
  local_10 = (float)*(double *)(in_EAX + 0x48) - *in_ECX;
  local_c = (float)*(double *)(in_EAX + 0x50) - in_ECX[1];
  local_8 = (float)*(double *)(in_EAX + 0x58) - in_ECX[2];
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
