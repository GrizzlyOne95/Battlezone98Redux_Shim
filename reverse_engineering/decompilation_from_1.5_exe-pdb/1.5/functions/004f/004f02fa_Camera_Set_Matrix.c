/*
 * Entry: 004f02fa
 * Name: Camera_Set_Matrix
 * Namespace: Global
 * Signature: void Camera_Set_Matrix(CAMERA * param_1, MAT_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Camera_Set_Matrix(CAMERA *param_1,MAT_3D *param_2)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  MAT_3D *pMVar8;
  float *pfVar9;
  int iVar10;
  double *pdVar11;
  VECTOR_3D_LONG *pVVar12;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar13;
  MAT_3D local_44;
  
  pMVar8 = param_2;
  param_1->View_Pyramid[0].x = param_2->posit_x;
  pdVar11 = &param_1->View_Pyramid[0].y;
  pVVar12 = param_1->View_Pyramid;
  *pdVar11 = param_2->posit_y;
  pfVar9 = &param_1->View_Frustrum[4].y;
  dVar1 = param_2->posit_z;
  param_2 = (MAT_3D *)0x4;
  param_1->View_Pyramid[0].z = dVar1;
  dVar2 = param_1->View_Pyramid[0].x;
  dVar3 = param_1->View_Pyramid[0].x;
  dVar4 = *pdVar11;
  dVar5 = *pdVar11;
  dVar6 = dVar1;
  do {
    pVVar12 = pVVar12 + 1;
    pVVar12->x = (double)(*pfVar9 * pMVar8->up_x +
                          pfVar9[1] * pMVar8->front_x +
                          ((VECTOR_3D *)(pfVar9 + -1))->x * pMVar8->right_x + (float)pMVar8->posit_x
                         );
    pVVar12->y = (double)(*pfVar9 * pMVar8->up_y +
                          ((VECTOR_3D *)(pfVar9 + -1))->x * pMVar8->right_y +
                          pMVar8->front_y * pfVar9[1] + (float)pMVar8->posit_y);
    dVar7 = (double)*pfVar9 * (double)pMVar8->up_z +
            (double)((VECTOR_3D *)(pfVar9 + -1))->x * (double)pMVar8->right_z +
            (double)pMVar8->front_z * (double)pfVar9[1] + pMVar8->posit_z;
    pVVar12->z = dVar7;
    if (pVVar12->x < dVar2) {
      dVar2 = pVVar12->x;
    }
    if (pVVar12->y < dVar4) {
      dVar4 = pVVar12->y;
    }
    if (dVar7 < dVar6) {
      dVar6 = dVar7;
    }
    if (dVar3 < pVVar12->x) {
      dVar3 = pVVar12->x;
    }
    if (dVar5 < pVVar12->y) {
      dVar5 = pVVar12->y;
    }
    if (dVar1 < dVar7) {
      dVar1 = dVar7;
    }
    pfVar9 = pfVar9 + 3;
    param_2 = (MAT_3D *)((int)&param_2[-1].posit_z + 7);
  } while (param_2 != (MAT_3D *)0x0);
  iVar10 = 5;
  dVar3 = (dVar3 + dVar2) * 0.5;
  (param_1->bSphere_Center).x = dVar3;
  dVar4 = (dVar5 + dVar4) * 0.5;
  (param_1->bSphere_Center).y = dVar4;
  dVar1 = (dVar1 + dVar6) * 0.5;
  (param_1->bSphere_Center).z = dVar1;
  dVar2 = 0.0;
  do {
    dVar6 = dVar3 - ((VECTOR_3D_LONG *)(pdVar11 + -1))->x;
    dVar7 = dVar4 - *pdVar11;
    dVar5 = dVar1 - pdVar11[1];
    dVar5 = dVar5 * dVar5 + dVar7 * dVar7 + dVar6 * dVar6;
    if (dVar2 < dVar5) {
      dVar2 = dVar5;
    }
    pdVar11 = pdVar11 + 3;
    iVar10 = iVar10 + -1;
  } while (iVar10 != 0);
  param_1->bSphere_Radius = SQRT(dVar2);
  pMVar8 = Matrix_Inverse(&local_44,unaff_EDI);
  pMVar13 = &param_1->Matrix;
  for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
    pMVar13->right_x = pMVar8->right_x;
    pMVar8 = (MAT_3D *)&pMVar8->right_y;
    pMVar13 = (MAT_3D *)&pMVar13->right_y;
  }
  return;
}
