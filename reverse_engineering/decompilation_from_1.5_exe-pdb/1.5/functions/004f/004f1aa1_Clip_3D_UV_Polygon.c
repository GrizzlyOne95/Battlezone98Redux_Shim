/*
 * Entry: 004f1aa1
 * Name: __Clip_3D_UV_Polygon
 * Namespace: Global
 * Signature: long __Clip_3D_UV_Polygon(CAMERA * param_1, POINT_3D * param_2, POINT_3D * param_3, long param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl
__Clip_3D_UV_Polygon(CAMERA *param_1,POINT_3D *param_2,POINT_3D *param_3,long param_4,long param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  long lVar5;
  float *pfVar6;
  int iVar7;
  POINT_3D *pPVar8;
  TEXEL *pTVar9;
  POINT_3D *pPVar10;
  long lVar11;
  POINT_3D *pPVar12;
  POINT_3D *pPVar13;
  POINT_3D *pPVar14;
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
  if (local_24 != 0) goto LAB_004f1aef;
  if (local_18 == 0) {
LAB_004f1dad:
    if (0 < param_4) {
      pfVar6 = &local_684.Vector.z;
      iVar7 = param_4;
      do {
        iVar7 = iVar7 + -1;
        fVar4 = 1.0 / (param_3->Vector).z;
        ((VECTOR_3D *)(pfVar6 + -2))->x =
             (param_3->Vector).x * fVar4 * param_1->Const_x + param_1->Orig_x;
        pfVar6[-1] = (param_3->Vector).y * param_1->Const_y * fVar4 + param_1->Orig_y;
        *pfVar6 = fVar4;
        *(TEXEL_u_8 *)(pfVar6 + 3) = (param_3->Texel).field2_0x8;
        pfVar6[1] = (param_3->Texel).u * fVar4;
        pfVar6[2] = fVar4 * (param_3->Texel).v;
        pfVar6 = pfVar6 + 6;
        param_3 = param_3 + 1;
      } while (0 < iVar7);
    }
    lVar5 = __Clip_2D_UV_Polygon(param_1,param_2,&local_684,param_4,param_5);
    if (((param_5 & 0x10U) == 0) && (0 < lVar5)) {
      pTVar9 = &param_2->Texel;
      lVar11 = lVar5;
      do {
        lVar11 = lVar11 + -1;
        fVar4 = 1.0 / (((POINT_3D *)(pTVar9 + -1))->Vector).z;
        pTVar9->u = fVar4 * pTVar9->u;
        pTVar9->v = fVar4 * pTVar9->v;
        pTVar9 = pTVar9 + 2;
      } while (0 < lVar11);
    }
  }
  else {
    pPVar10 = &local_684;
    if ((local_18 & 2) == 0) {
LAB_004f1c59:
      fVar4 = local_20;
      if ((local_18 & 1) == 0) goto LAB_004f1dad;
      local_8 = 0;
      local_10 = param_3 + param_4 + -1;
      if (0 < param_4) {
        local_c = pPVar10 + 1;
        local_14 = param_4;
        pPVar8 = param_3 + param_4 + -1;
        do {
          fVar1 = (pPVar8->Vector).z;
          if (fVar4 <= (param_3->Vector).z) {
            if (fVar1 < fVar4) {
              fVar1 = (fVar4 - (pPVar8->Vector).z) / ((param_3->Vector).z - (pPVar8->Vector).z);
              (pPVar10->Vector).z = fVar4;
              (pPVar10->Vector).x =
                   ((param_3->Vector).x - (pPVar8->Vector).x) * fVar1 + (pPVar8->Vector).x;
              (pPVar10->Vector).y =
                   ((param_3->Vector).y - (pPVar8->Vector).y) * fVar1 + (pPVar8->Vector).y;
              (pPVar10->Texel).u =
                   ((param_3->Texel).u - (pPVar8->Texel).u) * fVar1 + (pPVar8->Texel).u;
              (pPVar10->Texel).v =
                   ((param_3->Texel).v - (pPVar8->Texel).v) * fVar1 + (pPVar8->Texel).v;
              (pPVar10->Texel).field2_0x8.luma =
                   ((param_3->Texel).field2_0x8.luma - (pPVar8->Texel).field2_0x8.luma) * fVar1 +
                   (pPVar8->Texel).field2_0x8.luma;
              goto LAB_004f1d7e;
            }
          }
          else {
            iVar7 = 6;
            pPVar13 = param_3;
            pPVar12 = local_c;
            pPVar14 = pPVar10;
            if (fVar4 <= fVar1) {
              for (; iVar7 != 0; iVar7 = iVar7 + -1) {
                (pPVar12->Vector).x = (pPVar13->Vector).x;
                pPVar13 = (POINT_3D *)&(pPVar13->Vector).y;
                pPVar12 = (POINT_3D *)&(pPVar12->Vector).y;
              }
              fVar1 = (fVar4 - (pPVar8->Vector).z) / ((param_3->Vector).z - (pPVar8->Vector).z);
              local_c = local_c + 2;
              (pPVar10->Vector).z = fVar4;
              (pPVar10->Vector).x =
                   ((param_3->Vector).x - (pPVar8->Vector).x) * fVar1 + (pPVar8->Vector).x;
              local_8 = local_8 + 2;
              (pPVar10->Vector).y =
                   ((param_3->Vector).y - (pPVar8->Vector).y) * fVar1 + (pPVar8->Vector).y;
              (pPVar10->Texel).u =
                   ((param_3->Texel).u - (pPVar8->Texel).u) * fVar1 + (pPVar8->Texel).u;
              (pPVar10->Texel).v =
                   ((param_3->Texel).v - (pPVar8->Texel).v) * fVar1 + (pPVar8->Texel).v;
              (pPVar10->Texel).field2_0x8.luma =
                   ((param_3->Texel).field2_0x8.luma - (pPVar8->Texel).field2_0x8.luma) * fVar1 +
                   (pPVar8->Texel).field2_0x8.luma;
              pPVar10 = pPVar10 + 2;
            }
            else {
              for (; iVar7 != 0; iVar7 = iVar7 + -1) {
                (pPVar14->Vector).x = (pPVar13->Vector).x;
                pPVar13 = (POINT_3D *)&(pPVar13->Vector).y;
                pPVar14 = (POINT_3D *)&(pPVar14->Vector).y;
              }
LAB_004f1d7e:
              local_c = local_c + 1;
              local_8 = local_8 + 1;
              pPVar10 = pPVar10 + 1;
            }
          }
          local_10 = param_3;
          local_14 = local_14 + -1;
          pPVar8 = param_3;
          param_3 = param_3 + 1;
        } while (local_14 != 0);
        if (local_8 != 0) {
          param_3 = pPVar10 + -local_8;
          param_4 = local_8;
          goto LAB_004f1dad;
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
          pPVar13 = local_c;
          fVar1 = (param_3->Vector).z;
          fVar2 = (pPVar8->Vector).z;
          if (fVar4 < fVar1 == (fVar4 == fVar1)) {
            if (fVar4 < fVar2 != (fVar4 == fVar2)) {
              fVar1 = (fVar4 - (pPVar8->Vector).z) / ((param_3->Vector).z - (pPVar8->Vector).z);
              (pPVar10->Vector).z = fVar4;
              (pPVar10->Vector).x =
                   ((param_3->Vector).x - (pPVar8->Vector).x) * fVar1 + (pPVar8->Vector).x;
              (pPVar10->Vector).y =
                   ((param_3->Vector).y - (pPVar8->Vector).y) * fVar1 + (pPVar8->Vector).y;
              (pPVar10->Texel).u =
                   ((param_3->Texel).u - (pPVar8->Texel).u) * fVar1 + (pPVar8->Texel).u;
              (pPVar10->Texel).v =
                   ((param_3->Texel).v - (pPVar8->Texel).v) * fVar1 + (pPVar8->Texel).v;
              (pPVar10->Texel).field2_0x8.luma =
                   ((param_3->Texel).field2_0x8.luma - (pPVar8->Texel).field2_0x8.luma) * fVar1 +
                   (pPVar8->Texel).field2_0x8.luma;
              goto LAB_004f1c2a;
            }
          }
          else {
            iVar7 = 6;
            pPVar12 = param_3;
            pPVar14 = pPVar10;
            if (fVar4 < fVar2 == (fVar4 == fVar2)) {
              fVar1 = (pPVar8->Vector).z;
              fVar2 = (param_3->Vector).z;
              local_c = local_c + 2;
              fVar3 = (pPVar8->Vector).z;
              for (; iVar7 != 0; iVar7 = iVar7 + -1) {
                (pPVar13->Vector).x = (pPVar12->Vector).x;
                pPVar12 = (POINT_3D *)&(pPVar12->Vector).y;
                pPVar13 = (POINT_3D *)&(pPVar13->Vector).y;
              }
              fVar1 = (fVar4 - fVar1) / (fVar2 - fVar3);
              (pPVar10->Vector).z = fVar4;
              (pPVar10->Vector).x =
                   ((param_3->Vector).x - (pPVar8->Vector).x) * fVar1 + (pPVar8->Vector).x;
              local_8 = local_8 + 2;
              (pPVar10->Vector).y =
                   ((param_3->Vector).y - (pPVar8->Vector).y) * fVar1 + (pPVar8->Vector).y;
              (pPVar10->Texel).u =
                   ((param_3->Texel).u - (pPVar8->Texel).u) * fVar1 + (pPVar8->Texel).u;
              (pPVar10->Texel).v =
                   ((param_3->Texel).v - (pPVar8->Texel).v) * fVar1 + (pPVar8->Texel).v;
              (pPVar10->Texel).field2_0x8.luma =
                   ((param_3->Texel).field2_0x8.luma - (pPVar8->Texel).field2_0x8.luma) * fVar1 +
                   (pPVar8->Texel).field2_0x8.luma;
              pPVar10 = pPVar10 + 2;
            }
            else {
              for (; iVar7 != 0; iVar7 = iVar7 + -1) {
                (pPVar14->Vector).x = (pPVar12->Vector).x;
                pPVar12 = (POINT_3D *)&(pPVar12->Vector).y;
                pPVar14 = (POINT_3D *)&(pPVar14->Vector).y;
              }
LAB_004f1c2a:
              local_c = local_c + 1;
              local_8 = local_8 + 1;
              pPVar10 = pPVar10 + 1;
            }
          }
          local_10 = param_3;
          local_14 = local_14 + -1;
          pPVar8 = param_3;
          param_3 = param_3 + 1;
        } while (local_14 != 0);
        if (local_8 != 0) {
          param_3 = pPVar10 + -local_8;
          param_4 = local_8;
          goto LAB_004f1c59;
        }
      }
    }
LAB_004f1aef:
    lVar5 = 0;
  }
  return lVar5;
}
