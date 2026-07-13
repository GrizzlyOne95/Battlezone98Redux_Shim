/*
 * Entry: 0056d8d8
 * Name: Set_Camera_to_Path
 * Namespace: Global
 * Signature: void Set_Camera_to_Path(AiPath * param_1, long param_2, int * param_3, VECTOR_3D * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Set_Camera_to_Path(AiPath *param_1,long param_2,int *param_3,VECTOR_3D *param_4)

{
  int *in_EAX;
  float *pfVar1;
  MAT_3D *pMVar2;
  float *in_ECX;
  int iVar3;
  int unaff_EBX;
  VECTOR_3D *unaff_ESI;
  VECTOR_3D *unaff_EDI;
  MAT_3D *pMVar4;
  float fVar5;
  MAT_3D local_98;
  MAT_3D local_58;
  double local_18;
  float local_10;
  float local_c;
  float local_8;
  
  pfVar1 = (float *)(*(int *)(unaff_EBX + 8) + (int)param_1 * 8);
  local_18 = (double)((float)*in_EAX * 0.01);
  fVar5 = Terrain_FindFloor((double)*pfVar1,(double)pfVar1[1]);
  pfVar1 = (float *)(*(int *)(unaff_EBX + 8) + (int)param_1 * 8);
  local_10 = *pfVar1 - *in_ECX;
  local_c = (fVar5 + (float)local_18) - in_ECX[1];
  local_8 = pfVar1[1] - in_ECX[2];
  pMVar2 = Build_Directinal_Matrix(&local_98,unaff_EDI,unaff_ESI);
  pMVar4 = &local_58;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    pMVar4->right_x = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pMVar4 = (MAT_3D *)&pMVar4->right_y;
  }
  Camera_Set_Matrix(&View_Record.MainCam,&local_58);
  return;
}
