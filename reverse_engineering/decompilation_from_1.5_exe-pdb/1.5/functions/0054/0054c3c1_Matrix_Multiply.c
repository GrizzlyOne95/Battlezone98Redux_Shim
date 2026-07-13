/*
 * Entry: 0054c3c1
 * Name: Matrix_Multiply
 * Namespace: Global
 * Signature: MAT_3D * Matrix_Multiply(MAT_3D * __return_storage_ptr__, MAT_3D * param_1, MAT_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MAT_3D * __cdecl Matrix_Multiply(MAT_3D *__return_storage_ptr__,MAT_3D *param_1,MAT_3D *param_2)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  MAT_3D *pMVar22;
  MAT_3D *pMVar23;
  char cVar24;
  MAT_3D *pMVar25;
  
  cVar24 = '\x03';
  pMVar22 = __return_storage_ptr__;
  do {
    pMVar25 = param_1;
    pMVar23 = pMVar22;
    fVar2 = param_2->right_y;
    fVar3 = pMVar25->right_x;
    fVar4 = param_2->right_z;
    fVar5 = pMVar25->right_x;
    fVar6 = param_2->up_y;
    fVar7 = pMVar25->right_y;
    fVar8 = param_2->up_z;
    fVar9 = pMVar25->right_y;
    fVar10 = param_2->front_y;
    fVar11 = pMVar25->right_z;
    fVar12 = param_2->front_z;
    fVar13 = pMVar25->right_z;
    pMVar23->right_x =
         param_2->front_x * pMVar25->right_z +
         param_2->up_x * pMVar25->right_y + param_2->right_x * pMVar25->right_x;
    pMVar23->right_y = fVar10 * fVar11 + fVar6 * fVar7 + fVar2 * fVar3;
    pMVar23->right_z = fVar12 * fVar13 + fVar8 * fVar9 + fVar4 * fVar5;
    cVar24 = cVar24 + -1;
    pMVar22 = (MAT_3D *)&pMVar23->up_x;
    param_1 = (MAT_3D *)&pMVar25->up_x;
  } while (cVar24 != '\0');
  pfVar1 = &pMVar25->up_y;
  fVar2 = param_2->right_y;
  dVar14 = *(double *)pfVar1;
  fVar3 = param_2->right_z;
  dVar15 = *(double *)pfVar1;
  fVar4 = param_2->up_y;
  dVar16 = *(double *)&pMVar25->front_x;
  fVar5 = param_2->up_z;
  dVar17 = *(double *)&pMVar25->front_x;
  fVar6 = param_2->front_y;
  dVar18 = *(double *)&pMVar25->front_z;
  fVar7 = param_2->front_z;
  dVar19 = *(double *)&pMVar25->front_z;
  dVar20 = param_2->posit_y;
  dVar21 = param_2->posit_z;
  *(double *)&pMVar23->up_y =
       (double)(param_2->front_x * (float)*(double *)&pMVar25->front_z +
                param_2->up_x * (float)*(double *)&pMVar25->front_x +
                param_2->right_x * (float)*(double *)pfVar1 + (float)param_2->posit_x);
  *(double *)&pMVar23->front_z =
       (double)(fVar7 * (float)dVar19 + fVar5 * (float)dVar17 + fVar3 * (float)dVar15 +
               (float)dVar21);
  *(double *)&pMVar23->front_x =
       (double)(fVar6 * (float)dVar18 + fVar4 * (float)dVar16 + fVar2 * (float)dVar14 +
               (float)dVar20);
  return __return_storage_ptr__;
}
