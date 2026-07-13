/*
 * Entry: 0051d446
 * Name: Submit_Stars
 * Namespace: Global
 * Signature: void Submit_Stars(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Submit_Stars(CAMERA *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  MAT_3D *pMVar4;
  int iVar5;
  float *pfVar6;
  MAT_3D *pMVar7;
  MAT_3D local_88;
  MAT_3D local_48;
  int local_8;
  
  if ((StarSet.starCount != 0) && (local_8 = StarSet.starCount, 0 < StarSet.starCount)) {
    pfVar6 = &VisibleStar[0].azimuth;
    do {
      pMVar4 = Build_Position_Rotation_Matrix
                         (&local_88,pfVar6[1],*pfVar6,pfVar6[2],(float)param_1->View_Pyramid[0].x,
                          (float)param_1->View_Pyramid[0].y,(float)param_1->View_Pyramid[0].z);
      pMVar7 = &local_48;
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        pMVar7->right_x = pMVar4->right_x;
        pMVar4 = (MAT_3D *)&pMVar4->right_y;
        pMVar7 = (MAT_3D *)&pMVar7->right_y;
      }
      pMVar4 = Matrix_Multiply(&local_88,&local_48,&param_1->Matrix);
      fVar3 = (float)local_8;
      fVar2 = pfVar6[-2];
      fVar1 = pfVar6[3];
      pMVar7 = &local_48;
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        pMVar7->right_x = pMVar4->right_x;
        pMVar4 = (MAT_3D *)&pMVar4->right_y;
        pMVar7 = (MAT_3D *)&pMVar7->right_y;
      }
      GenerateStarPoly(param_1,(TEXTURE *)pfVar6[-3],&local_48,pfVar6[-1] * 0.5,fVar1 - fVar3,
                       (int)fVar2);
      local_8 = local_8 + -1;
      pfVar6 = pfVar6 + 0xb;
    } while (0 < local_8);
  }
  return;
}
