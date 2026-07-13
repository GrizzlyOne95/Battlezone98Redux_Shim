/*
 * Entry: 00472992
 * Name: GeomBox
 * Namespace: Global
 * Signature: int GeomBox(_OBJ76 * param_1, MAT_3D * param_2, BOX_INFO * param_3, float param_4, CLSN_INFO * param_5, CLSN_INFO * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Unable to track spacebase fully for stack */

int __cdecl
GeomBox(_OBJ76 *param_1,MAT_3D *param_2,BOX_INFO *param_3,float param_4,CLSN_INFO *param_5,
       CLSN_INFO *param_6)

{
  float fVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined1 *puVar5;
  int *piVar6;
  MAT_3D *pMVar7;
  VECTOR_3D *pVVar8;
  EULER *pEVar9;
  int iVar10;
  int *unaff_EBX;
  BBOX *pBVar11;
  float *pfVar12;
  float *pfVar13;
  EULER *pEVar14;
  int iStack_17c;
  POINT_VEL PStack_178;
  BBOX BStack_160;
  undefined1 auStack_148 [8];
  float afStack_140 [2];
  int iStack_138;
  undefined1 local_12c [8];
  undefined1 local_124 [64];
  float local_e4 [16];
  undefined1 local_a4 [12];
  float local_98 [4];
  float fStack_88;
  float fStack_84;
  float local_80;
  float fStack_7c;
  float fStack_78;
  int local_74;
  int iStack_70;
  int iStack_6c;
  float local_68 [4];
  float fStack_58;
  float fStack_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  undefined1 local_38 [12];
  float local_2c;
  float local_28;
  float local_24;
  int local_20;
  MAT_3D *local_1c;
  int *local_18;
  undefined1 *local_14;
  int *local_10;
  int *local_c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_68;
  local_18 = param_1->clsnInfo;
  iVar3 = *local_18;
  local_c = (int *)local_18[1];
  iStack_138 = 0x4729c5;
  iVar4 = iVar3 * -0xc;
  local_14 = local_124 + iVar4 + -0x10;
  (&iStack_138)[iVar3 * -3] = (int)local_124;
  local_1c = &param_3->mat;
  afStack_140[iVar3 * -3 + 1] = 6.535338e-39;
  pMVar7 = Matrix_Inverse((MAT_3D *)(&iStack_138)[iVar3 * -3],
                          *(MAT_3D **)(local_124 + iVar4 + -0x10));
  afStack_140[iVar3 * -3 + 1] = 2.24208e-44;
  iVar10 = (int)afStack_140[iVar3 * -3 + 1];
  afStack_140[iVar3 * -3 + 1] = (float)local_e4;
  afStack_140[iVar3 * -3] = (float)param_2;
  *(undefined1 **)(auStack_148 + iVar4 + 4) = local_124;
  pfVar12 = local_e4;
  for (; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pfVar12 = pMVar7->right_x;
    pMVar7 = (MAT_3D *)&pMVar7->right_y;
    pfVar12 = pfVar12 + 1;
  }
  *(undefined4 *)(auStack_148 + iVar4) = 0x4729fa;
  pMVar7 = Matrix_Multiply(*(MAT_3D **)(auStack_148 + iVar4 + 4),(MAT_3D *)afStack_140[iVar3 * -3],
                           (MAT_3D *)afStack_140[iVar3 * -3 + 1]);
  *(undefined4 *)(auStack_148 + iVar4) = 0x10;
  pfVar12 = local_e4;
  for (iVar10 = *(int *)(auStack_148 + iVar4); puVar5 = local_14, piVar2 = local_18, iVar10 != 0;
      iVar10 = iVar10 + -1) {
    *pfVar12 = pMVar7->right_x;
    pMVar7 = (MAT_3D *)&pMVar7->right_y;
    pfVar12 = pfVar12 + 1;
  }
  *(float **)(auStack_148 + iVar4) = local_e4;
  *(int *)(auStack_148 + iVar4 + -4) = *piVar2;
  *(int **)(auStack_148 + iVar4 + -8) = local_c;
  *(undefined1 **)(auStack_148 + iVar4 + -0xc) = puVar5;
  *(undefined4 *)(auStack_148 + iVar4 + -0x10) = 0x472a19;
  Vector_Transform(*(VECTOR_3D **)(auStack_148 + iVar4 + -0xc),
                   *(VECTOR_3D **)(auStack_148 + iVar4 + -8),*(long *)(auStack_148 + iVar4 + -4),
                   *(MAT_3D **)(auStack_148 + iVar4));
  local_10 = local_c;
  unaff_EBX[0x14] = (int)param_4;
  *unaff_EBX = 0;
  local_14 = (undefined1 *)0x0;
  if (0 < *piVar2) {
    local_c = (int *)((int)puVar5 - (int)local_c);
    do {
      afStack_140[iVar3 * -3 + 1] = (float)param_1;
      piVar6 = local_10;
      piVar2 = local_10 + 1;
      *(int *)(auStack_148 + iVar4) = *local_10;
      *(int *)(auStack_148 + iVar4 + 4) = *piVar2;
      *(undefined1 **)(auStack_148 + iVar4 + -4) = local_a4;
      afStack_140[iVar3 * -3] = (float)piVar6[2];
      *(undefined4 *)(auStack_148 + iVar4 + -8) = 0x472a54;
      pVVar8 = WorldVelocity(*(VECTOR_3D **)(auStack_148 + iVar4 + -4),
                             *(VECTOR_3D *)(auStack_148 + iVar4),
                             (_OBJ76 *)afStack_140[iVar3 * -3 + 1]);
      local_44 = (param_3->pv).v.x;
      local_40 = (param_3->pv).v.y;
      local_3c = (param_3->pv).v.z;
      local_50 = pVVar8->x;
      local_4c = pVVar8->y;
      *(MAT_3D **)(auStack_148 + iVar4 + -8) = local_1c;
      fVar1 = local_4c;
      local_48 = pVVar8->z;
      local_2c = local_50 - local_44;
      *(float **)(auStack_148 + iVar4 + -0xc) = &local_80;
      fVar1 = fVar1 - local_40;
      *(undefined1 **)(auStack_148 + iVar4 + -0x10) = local_38;
      local_28 = fVar1;
      local_24 = local_48 - local_3c;
      local_80 = local_2c;
      fStack_7c = fVar1;
      fStack_78 = local_48 - local_3c;
      *(undefined4 *)(auStack_148 + iVar4 + -0x14) = 0x472a9c;
      pVVar8 = Vector_Unrotate(*(VECTOR_3D **)(auStack_148 + iVar4 + -0x10),
                               *(VECTOR_3D **)(auStack_148 + iVar4 + -0xc),
                               *(MAT_3D **)(auStack_148 + iVar4 + -8));
      local_68[3] = pVVar8->x;
      fStack_58 = pVVar8->y;
      fStack_54 = pVVar8->z;
      pfVar12 = (float *)((int)local_c + (int)local_10);
      afStack_140[iVar3 * -3 + 1] = 0.0;
      afStack_140[iVar3 * -3] = (float)&local_74;
      iVar10 = unaff_EBX[0x14];
      local_68[0] = *pfVar12;
      local_68[1] = pfVar12[1];
      *(int **)(auStack_148 + iVar4 + 4) = &local_20;
      local_68[2] = pfVar12[2];
      *(int *)(auStack_148 + iVar4) = iVar10;
      *(undefined4 *)((int)&PStack_178 + iVar4 + 0x14) = 6;
      pBVar11 = &param_3->box;
      pfVar12 = (float *)((int)&BStack_160 + iVar4);
      for (iVar10 = *(int *)((int)&PStack_178 + iVar4 + 0x14); iVar10 != 0; iVar10 = iVar10 + -1) {
        *pfVar12 = (pBVar11->min).x;
        pBVar11 = (BBOX *)&(pBVar11->min).y;
        pfVar12 = pfVar12 + 1;
      }
      (&iStack_17c)[iVar3 * -3] = 6;
      pfVar12 = local_68;
      pfVar13 = (float *)((int)&PStack_178 + iVar4);
      for (iVar10 = (&iStack_17c)[iVar3 * -3]; iVar10 != 0; iVar10 = iVar10 + -1) {
        *pfVar13 = *pfVar12;
        pfVar12 = pfVar12 + 1;
        pfVar13 = pfVar13 + 1;
      }
      (&iStack_17c)[iVar3 * -3] = 0x472aec;
      iVar10 = PointBox(*(POINT_VEL *)((int)&PStack_178 + iVar4),*(BBOX *)((int)&BStack_160 + iVar4)
                        ,*(float *)(auStack_148 + iVar4),*(float **)(auStack_148 + iVar4 + 4),
                        (VECTOR_3D *)afStack_140[iVar3 * -3],afStack_140[iVar3 * -3 + 1]);
      if (iVar10 != 0) {
        *unaff_EBX = 1;
        unaff_EBX[0x15] = *local_10;
        unaff_EBX[0x16] = local_10[1];
        unaff_EBX[0x17] = local_10[2];
        unaff_EBX[0x14] = local_20;
        unaff_EBX[0x18] = (int)local_2c;
        unaff_EBX[0x19] = (int)local_28;
        unaff_EBX[0x1a] = (int)local_24;
        unaff_EBX[0x1b] = local_74;
        unaff_EBX[0x1c] = iStack_70;
        unaff_EBX[0x1d] = iStack_6c;
        afStack_140[iVar3 * -3 + 1] = 8.40779e-45;
        pfVar12 = local_68;
        pfVar13 = local_98;
        for (iVar10 = (int)afStack_140[iVar3 * -3 + 1]; iVar10 != 0; iVar10 = iVar10 + -1) {
          *pfVar13 = *pfVar12;
          pfVar12 = pfVar12 + 1;
          pfVar13 = pfVar13 + 1;
        }
      }
      local_14 = (undefined1 *)((int)local_14 + 1);
      local_10 = local_10 + 3;
    } while ((int)local_14 < *local_18);
    if (*unaff_EBX != 0) {
      unaff_EBX[1] = (int)param_3->obj;
      afStack_140[iVar3 * -3 + 1] = (float)param_3->obj;
      afStack_140[iVar3 * -3] = (float)local_12c;
      *(undefined4 *)(auStack_148 + iVar4 + 4) = 0x472b5b;
      pEVar9 = ClassGetEuler((EULER *)afStack_140[iVar3 * -3],(_OBJ76 *)afStack_140[iVar3 * -3 + 1])
      ;
      *(undefined4 *)(auStack_148 + iVar4 + 4) = 0x12;
      pfVar12 = (float *)(unaff_EBX + 2);
      for (iVar10 = *(int *)(auStack_148 + iVar4 + 4); iVar10 != 0; iVar10 = iVar10 + -1) {
        *pfVar12 = pEVar9->mass;
        pEVar9 = (EULER *)&pEVar9->mass_inv;
        pfVar12 = pfVar12 + 1;
      }
      *(_OBJ76 **)(auStack_148 + iVar4 + 4) = param_1;
      param_5->obj = param_1;
      *(undefined1 **)(auStack_148 + iVar4) = local_12c;
      param_5->collided = 1;
      *(undefined4 *)(auStack_148 + iVar4 + -4) = 0x472b81;
      pEVar9 = ClassGetEuler(*(EULER **)(auStack_148 + iVar4),*(_OBJ76 **)(auStack_148 + iVar4 + 4))
      ;
      *(undefined4 *)(auStack_148 + iVar4 + -4) = 0x12;
      pEVar14 = &param_5->euler;
      for (iVar10 = *(int *)(auStack_148 + iVar4 + -4); iVar10 != 0; iVar10 = iVar10 + -1) {
        pEVar14->mass = pEVar9->mass;
        pEVar9 = (EULER *)&pEVar9->mass_inv;
        pEVar14 = (EULER *)&pEVar14->mass_inv;
      }
      fVar1 = (float)unaff_EBX[0x14];
      param_5->t = fVar1;
      *(float *)(auStack_148 + iVar4 + 4) = local_98[3];
      afStack_140[iVar3 * -3] = fStack_88;
      afStack_140[iVar3 * -3 + 1] = fStack_84;
      *(float *)(auStack_148 + iVar4) = fVar1;
      *(float *)(auStack_148 + iVar4 + -0xc) = local_98[0];
      *(float *)(auStack_148 + iVar4 + -8) = local_98[1];
      *(undefined1 **)(auStack_148 + iVar4 + -0x10) = local_38;
      *(float *)(auStack_148 + iVar4 + -4) = local_98[2];
      *(undefined4 *)(auStack_148 + iVar4 + -0x14) = 0x472bb7;
      pVVar8 = AddMultVectors(*(VECTOR_3D **)(auStack_148 + iVar4 + -0x10),
                              *(VECTOR_3D *)(auStack_148 + iVar4 + -0xc),
                              *(float *)(auStack_148 + iVar4),
                              *(VECTOR_3D *)(auStack_148 + iVar4 + 4));
      (param_5->point).x = pVVar8->x;
      (param_5->point).y = pVVar8->y;
      (param_5->point).z = pVVar8->z;
      (param_5->vel).x = (float)unaff_EBX[0x18];
      (param_5->vel).y = (float)unaff_EBX[0x19];
      (param_5->vel).z = (float)unaff_EBX[0x1a];
      *(int *)(auStack_148 + iVar4 + 4) = unaff_EBX[0x18];
      afStack_140[iVar3 * -3] = (float)unaff_EBX[0x19];
      *(undefined1 **)(auStack_148 + iVar4) = local_38;
      afStack_140[iVar3 * -3 + 1] = (float)unaff_EBX[0x1a];
      *(undefined4 *)(auStack_148 + iVar4 + -4) = 0x472be0;
      pVVar8 = NegVector(*(VECTOR_3D **)(auStack_148 + iVar4),
                         *(VECTOR_3D *)(auStack_148 + iVar4 + 4));
      *(MAT_3D **)(auStack_148 + iVar4 + -4) = local_1c;
      unaff_EBX[0x18] = (int)pVVar8->x;
      unaff_EBX[0x19] = (int)pVVar8->y;
      unaff_EBX[0x1a] = (int)pVVar8->z;
      *(int **)(auStack_148 + iVar4 + -8) = unaff_EBX + 0x1b;
      *(undefined1 **)(auStack_148 + iVar4 + -0xc) = local_38;
      *(undefined4 *)(auStack_148 + iVar4 + -0x10) = 0x472bf8;
      pVVar8 = Vector_Rotate(*(VECTOR_3D **)(auStack_148 + iVar4 + -0xc),
                             *(VECTOR_3D **)(auStack_148 + iVar4 + -8),
                             *(MAT_3D **)(auStack_148 + iVar4 + -4));
      unaff_EBX[0x1b] = (int)pVVar8->x;
      unaff_EBX[0x1c] = (int)pVVar8->y;
      unaff_EBX[0x1d] = (int)pVVar8->z;
      *(float *)(auStack_148 + iVar4 + 4) = pVVar8->x;
      afStack_140[iVar3 * -3] = pVVar8->y;
      *(undefined1 **)(auStack_148 + iVar4) = local_38;
      afStack_140[iVar3 * -3 + 1] = pVVar8->z;
      *(undefined4 *)(auStack_148 + iVar4 + -4) = 0x472c10;
      pVVar8 = NegVector(*(VECTOR_3D **)(auStack_148 + iVar4),
                         *(VECTOR_3D *)(auStack_148 + iVar4 + 4));
      (param_5->normal).x = pVVar8->x;
      (param_5->normal).y = pVVar8->y;
      (param_5->normal).z = pVVar8->z;
      return 1;
    }
  }
  return 0;
}
