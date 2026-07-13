/*
 * Entry: 004eae44
 * Name: ComputeRenderQuality
 * Namespace: Global
 * Signature: void ComputeRenderQuality(CAMERA * param_1, long param_2, long param_3, long * param_4, long * param_5, tagENTITY * * param_6, tagENTITY * * param_7, VECTOR_3D * param_8, VECTOR_3D * param_9)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
ComputeRenderQuality
          (CAMERA *param_1,long param_2,long param_3,long *param_4,long *param_5,tagENTITY **param_6
          ,tagENTITY **param_7,VECTOR_3D *param_8,VECTOR_3D *param_9)

{
  uchar uVar1;
  float fVar2;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  int extraout_EAX_03;
  int extraout_EAX_04;
  uint *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  VECTOR_3D *pVVar9;
  int iVar10;
  int iVar11;
  long local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_14 = param_2;
  iVar8 = 0;
  iVar10 = -1;
  entityHead = -1;
  entityCount = 0;
  iVar11 = entityCount;
  iVar4 = entityHead;
  if (0 < param_3) {
    do {
      _ftol2_sse();
      _ftol2_sse();
      _ftol2_sse();
      iVar4 = extraout_EAX_01 * extraout_EAX_01 + extraout_EAX_00 * extraout_EAX_00 +
              extraout_EAX * extraout_EAX;
      iVar11 = iVar8 + 1;
      entityDist[iVar8] = iVar4;
      entityEnt[iVar8] = iVar11;
      if (iVar10 == -1) {
        entityLink[iVar8] = -1;
        iVar10 = iVar8;
      }
      else {
        iVar6 = entityLink[iVar10];
        local_10 = iVar10;
        if (entityDist[iVar10] < iVar4) {
          while ((iVar5 = iVar6, -1 < iVar5 && (entityDist[iVar5] < iVar4))) {
            local_10 = iVar5;
            iVar6 = entityLink[iVar5];
          }
          entityLink[iVar8] = entityLink[local_10];
          entityLink[local_10] = iVar8;
        }
        else {
          entityLink[iVar8] = iVar10;
          iVar10 = iVar8;
        }
      }
      iVar8 = iVar11;
      iVar4 = iVar10;
    } while (iVar11 < param_3);
  }
  entityHead = iVar4;
  entityCount = iVar11;
  iVar8 = entityCount;
  iVar11 = entityHead;
  if (0 < param_2) {
    param_2 = -1;
    do {
      _ftol2_sse();
      _ftol2_sse();
      _ftol2_sse();
      iVar10 = extraout_EAX_04 * extraout_EAX_04 + extraout_EAX_03 * extraout_EAX_03 +
               extraout_EAX_02 * extraout_EAX_02;
      entityDist[iVar8] = iVar10;
      entityEnt[iVar8] = param_2;
      if (iVar11 == -1) {
        entityLink[iVar8] = -1;
        iVar11 = iVar8;
      }
      else {
        iVar4 = entityLink[iVar11];
        local_10 = iVar11;
        if (entityDist[iVar11] < iVar10) {
          while ((iVar6 = iVar4, -1 < iVar6 && (entityDist[iVar6] < iVar10))) {
            local_10 = iVar6;
            iVar4 = entityLink[iVar6];
          }
          entityLink[iVar8] = entityLink[local_10];
          entityLink[local_10] = iVar8;
        }
        else {
          entityLink[iVar8] = iVar11;
          iVar11 = iVar8;
        }
      }
      iVar8 = iVar8 + 1;
      param_2 = param_2 + -1;
      local_14 = local_14 + -1;
    } while (local_14 != 0);
  }
  entityHead = iVar11;
  entityCount = iVar8;
  fVar2 = 1.0 / param_1->Const_x;
  param_1 = (CAMERA *)0x0;
  local_c = 0;
  local_8 = 0;
  local_10 = 0;
  param_3 = 0;
  iVar11 = entityHead;
  if (0 < entityCount) {
    do {
      if (0x7f < param_3) {
        return;
      }
      iVar8 = entityEnt[iVar11];
      uVar7 = 0;
      if (iVar8 < 1) {
        param_2 = *(long *)((int)param_6 - (iVar8 * 4 + 4));
        pVVar9 = param_8 + -(iVar8 + 1);
      }
      else {
        param_2 = (long)param_7[iVar8 + -1];
        pVVar9 = param_9 + iVar8 + -1;
      }
      uVar1 = (UserProfilePtr->graphicDetail).objDetail;
      if (uVar1 == '\0') {
        uVar7 = 0xd;
      }
      else if (uVar1 == '\x01') {
        if (*(int *)(*(int *)param_2 + 0xac) != 7) {
          uVar7 = ComputeFlag((tagENTITY *)param_2,pVVar9->z * fVar2,entityDist[iVar11],param_3,
                              (int)&param_1->Orig_x + local_8,local_10 + local_c);
          goto LAB_004eb110;
        }
LAB_004eb0c4:
        uVar7 = 0;
      }
      else if (uVar1 == '\x02') {
        if (*(int *)(*(int *)param_2 + 0xac) == 7) {
          uVar7 = 0;
        }
        else {
          uVar7 = ComputeFlag((tagENTITY *)param_2,pVVar9->z * fVar2,entityDist[iVar11],param_3,
                              (int)&param_1->Orig_x + local_8,local_10 + local_c);
          uVar7 = uVar7 & 0x10 | 4;
        }
LAB_004eb110:
        uVar7 = uVar7 | 4;
      }
      else if (uVar1 == '\x03') goto LAB_004eb0c4;
      iVar8 = GetTerrainLuma(*(double *)(*(int *)param_2 + 0x48),*(double *)(*(int *)param_2 + 0x58)
                            );
      if (iVar8 <= inShadow) {
        uVar7 = uVar7 | 0x40;
      }
      if ((UserProfilePtr->graphicDetail).shadow == '\0') {
        uVar7 = uVar7 | 0x20;
      }
      iVar8 = entityEnt[iVar11];
      if (iVar8 < 1) {
        puVar3 = (uint *)((int)param_4 - (iVar8 * 4 + 4));
        *puVar3 = *puVar3 | uVar7;
        if ((uVar7 & 1) == 0) {
          local_8 = local_8 + 1;
        }
        if ((uVar7 & 2) == 0) {
          local_10 = local_10 + 1;
        }
      }
      else {
        param_5[iVar8 + -1] = param_5[iVar8 + -1] | uVar7;
        if ((uVar7 & 1) == 0) {
          param_1 = (CAMERA *)((int)&param_1->Orig_x + 1);
        }
        if ((uVar7 & 2) == 0) {
          local_c = local_c + 1;
        }
      }
      param_3 = param_3 + 1;
      iVar11 = entityLink[iVar11];
    } while (param_3 < entityCount);
  }
  return;
}
