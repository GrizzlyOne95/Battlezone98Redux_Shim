/*
 * Entry: 004f17b3
 * Name: __Clip_3D_Polygon
 * Namespace: Global
 * Signature: long __Clip_3D_Polygon(CAMERA * param_1, POINT_3D * param_2, POINT_3D * param_3, long param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl
__Clip_3D_Polygon(CAMERA *param_1,POINT_3D *param_2,POINT_3D *param_3,long param_4,long param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  long lVar5;
  float *pfVar6;
  int iVar7;
  POINT_3D *pPVar8;
  POINT_3D *pPVar9;
  POINT_3D *pPVar10;
  POINT_3D *pPVar11;
  POINT_3D *pPVar12;
  POINT_3D local_684;
  POINT_3D local_66c [67];
  int local_24;
  float local_20;
  float local_1c;
  uint local_18;
  int local_14;
  POINT_3D *local_10;
  POINT_3D *local_c;
  int local_8;
  
  local_1c = param_1->View_Frustrum[0].z;
  local_20 = param_1->View_Frustrum[4].z;
  Compute_Outcode_Z(&local_24,(long *)&local_18,param_3,param_4,local_1c,local_20);
  fVar4 = local_1c;
  if (local_24 != 0) goto LAB_004f1801;
  if (local_18 == 0) {
LAB_004f1a47:
    if (0 < param_4) {
      pfVar6 = &local_684.Vector.z;
      iVar7 = param_4;
      do {
        iVar7 = iVar7 + -1;
        fVar4 = 1.0 / (param_3->Vector).z;
        ((VECTOR_3D *)(pfVar6 + -2))->x =
             param_1->Const_x * (param_3->Vector).x * fVar4 + param_1->Orig_x;
        pfVar6[-1] = (param_3->Vector).y * param_1->Const_y * fVar4 + param_1->Orig_y;
        *pfVar6 = fVar4;
        *(TEXEL_u_8 *)(pfVar6 + 3) = (param_3->Texel).field2_0x8;
        pfVar6 = pfVar6 + 6;
        param_3 = param_3 + 1;
      } while (0 < iVar7);
    }
    lVar5 = __Clip_2D_Polygon(param_1,param_2,&local_684,param_4,param_5);
  }
  else {
    pPVar9 = &local_684;
    if ((local_18 & 2) == 0) {
LAB_004f192f:
      fVar4 = local_20;
      if ((local_18 & 1) == 0) goto LAB_004f1a47;
      local_8 = 0;
      local_10 = param_3 + param_4 + -1;
      if (0 < param_4) {
        local_c = pPVar9 + 1;
        local_14 = param_4;
        pPVar8 = param_3 + param_4 + -1;
        do {
          fVar1 = (pPVar8->Vector).z;
          if (fVar4 <= (param_3->Vector).z) {
            if (fVar1 < fVar4) {
              fVar1 = (fVar4 - (pPVar8->Vector).z) / ((param_3->Vector).z - (pPVar8->Vector).z);
              (pPVar9->Vector).z = fVar4;
              (pPVar9->Vector).x =
                   ((param_3->Vector).x - (pPVar8->Vector).x) * fVar1 + (pPVar8->Vector).x;
              (pPVar9->Vector).y =
                   ((param_3->Vector).y - (pPVar8->Vector).y) * fVar1 + (pPVar8->Vector).y;
              (pPVar9->Texel).field2_0x8.luma =
                   ((param_3->Texel).field2_0x8.luma - (pPVar8->Texel).field2_0x8.luma) * fVar1 +
                   (pPVar8->Texel).field2_0x8.luma;
              goto LAB_004f1a18;
            }
          }
          else {
            iVar7 = 6;
            pPVar11 = param_3;
            pPVar10 = local_c;
            pPVar12 = pPVar9;
            if (fVar4 <= fVar1) {
              for (; iVar7 != 0; iVar7 = iVar7 + -1) {
                (pPVar10->Vector).x = (pPVar11->Vector).x;
                pPVar11 = (POINT_3D *)&(pPVar11->Vector).y;
                pPVar10 = (POINT_3D *)&(pPVar10->Vector).y;
              }
              fVar1 = (fVar4 - (pPVar8->Vector).z) / ((param_3->Vector).z - (pPVar8->Vector).z);
              local_c = local_c + 2;
              (pPVar9->Vector).z = fVar4;
              (pPVar9->Vector).x =
                   ((param_3->Vector).x - (pPVar8->Vector).x) * fVar1 + (pPVar8->Vector).x;
              local_8 = local_8 + 2;
              (pPVar9->Vector).y =
                   ((param_3->Vector).y - (pPVar8->Vector).y) * fVar1 + (pPVar8->Vector).y;
              (pPVar9->Texel).field2_0x8.luma =
                   ((param_3->Texel).field2_0x8.luma - (pPVar8->Texel).field2_0x8.luma) * fVar1 +
                   (pPVar8->Texel).field2_0x8.luma;
              pPVar9 = pPVar9 + 2;
            }
            else {
              for (; iVar7 != 0; iVar7 = iVar7 + -1) {
                (pPVar12->Vector).x = (pPVar11->Vector).x;
                pPVar11 = (POINT_3D *)&(pPVar11->Vector).y;
                pPVar12 = (POINT_3D *)&(pPVar12->Vector).y;
              }
LAB_004f1a18:
              local_c = local_c + 1;
              local_8 = local_8 + 1;
              pPVar9 = pPVar9 + 1;
            }
          }
          local_10 = param_3;
          local_14 = local_14 + -1;
          pPVar8 = param_3;
          param_3 = param_3 + 1;
        } while (local_14 != 0);
        if (local_8 != 0) {
          param_3 = pPVar9 + -local_8;
          param_4 = local_8;
          goto LAB_004f1a47;
        }
      }
    }
    else {
      local_8 = 0;
      if (0 < param_4) {
        local_c = local_66c;
        local_14 = param_4;
        pPVar8 = param_3 + param_4 + -1;
        do {
          pPVar11 = local_c;
          fVar1 = (param_3->Vector).z;
          fVar2 = (pPVar8->Vector).z;
          if (fVar4 < fVar1 == (fVar4 == fVar1)) {
            if (fVar4 < fVar2 != (fVar4 == fVar2)) {
              fVar1 = (fVar4 - (pPVar8->Vector).z) / ((param_3->Vector).z - (pPVar8->Vector).z);
              (pPVar9->Vector).z = fVar4;
              (pPVar9->Vector).x =
                   ((param_3->Vector).x - (pPVar8->Vector).x) * fVar1 + (pPVar8->Vector).x;
              (pPVar9->Vector).y =
                   ((param_3->Vector).y - (pPVar8->Vector).y) * fVar1 + (pPVar8->Vector).y;
              (pPVar9->Texel).field2_0x8.luma =
                   ((param_3->Texel).field2_0x8.luma - (pPVar8->Texel).field2_0x8.luma) * fVar1 +
                   (pPVar8->Texel).field2_0x8.luma;
              goto LAB_004f1900;
            }
          }
          else {
            iVar7 = 6;
            pPVar10 = param_3;
            pPVar12 = pPVar9;
            if (fVar4 < fVar2 == (fVar4 == fVar2)) {
              fVar1 = (pPVar8->Vector).z;
              fVar2 = (param_3->Vector).z;
              local_c = local_c + 2;
              fVar3 = (pPVar8->Vector).z;
              for (; iVar7 != 0; iVar7 = iVar7 + -1) {
                (pPVar11->Vector).x = (pPVar10->Vector).x;
                pPVar10 = (POINT_3D *)&(pPVar10->Vector).y;
                pPVar11 = (POINT_3D *)&(pPVar11->Vector).y;
              }
              fVar1 = (fVar4 - fVar1) / (fVar2 - fVar3);
              (pPVar9->Vector).z = fVar4;
              (pPVar9->Vector).x =
                   ((param_3->Vector).x - (pPVar8->Vector).x) * fVar1 + (pPVar8->Vector).x;
              local_8 = local_8 + 2;
              (pPVar9->Vector).y =
                   ((param_3->Vector).y - (pPVar8->Vector).y) * fVar1 + (pPVar8->Vector).y;
              (pPVar9->Texel).field2_0x8.luma =
                   ((param_3->Texel).field2_0x8.luma - (pPVar8->Texel).field2_0x8.luma) * fVar1 +
                   (pPVar8->Texel).field2_0x8.luma;
              pPVar9 = pPVar9 + 2;
            }
            else {
              for (; iVar7 != 0; iVar7 = iVar7 + -1) {
                (pPVar12->Vector).x = (pPVar10->Vector).x;
                pPVar10 = (POINT_3D *)&(pPVar10->Vector).y;
                pPVar12 = (POINT_3D *)&(pPVar12->Vector).y;
              }
LAB_004f1900:
              local_c = local_c + 1;
              local_8 = local_8 + 1;
              pPVar9 = pPVar9 + 1;
            }
          }
          local_10 = param_3;
          local_14 = local_14 + -1;
          pPVar8 = param_3;
          param_3 = param_3 + 1;
        } while (local_14 != 0);
        if (local_8 != 0) {
          param_3 = pPVar9 + -local_8;
          param_4 = local_8;
          goto LAB_004f192f;
        }
      }
    }
LAB_004f1801:
    lVar5 = 0;
  }
  return lVar5;
}
