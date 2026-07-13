/*
 * Entry: 005423c2
 * Name: D3D_Clip_3D_Polygon
 * Namespace: Global
 * Signature: long D3D_Clip_3D_Polygon(CAMERA * param_1, POINT_3D * param_2, POINT_3D * param_3, long param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl
D3D_Clip_3D_Polygon(CAMERA *param_1,POINT_3D *param_2,POINT_3D *param_3,long param_4,long param_5)

{
  float fVar1;
  float fVar2;
  tagLIGHTING *ptVar3;
  long lVar4;
  int iVar5;
  POINT_3D *pPVar6;
  POINT_3D *pPVar7;
  float unaff_EBX;
  tagLIGHTING *unaff_ESI;
  POINT_3D *pPVar8;
  tagLIGHTING *unaff_EDI;
  POINT_3D *pPVar9;
  POINT_3D local_68c;
  POINT_3D local_674 [67];
  int local_2c;
  float local_28;
  float local_24;
  uint local_20;
  int local_1c;
  POINT_3D *local_18;
  POINT_3D *local_14;
  int local_10;
  POINT_3D *local_c;
  TEXEL_u_8 *local_8;
  
  local_28 = param_1->View_Frustrum[0].z;
  local_24 = param_1->View_Frustrum[4].z;
  Compute_Outcode_Z(&local_2c,(long *)&local_20,param_3,param_4,local_28,local_24);
  if (local_2c != 0) {
    return 0;
  }
  if (local_20 == 0) {
LAB_005426dd:
    D3D_Clip_3D_Project_Only(param_1,&local_68c,param_3,param_4,param_5);
    lVar4 = D3D_Clip_2D_Polygon(param_1,param_2,&local_68c,param_4,param_5);
  }
  else {
    pPVar7 = &local_68c;
    local_14 = pPVar7;
    pPVar6 = param_3;
    if ((local_20 & 2) == 0) {
LAB_005424c8:
      param_3 = pPVar6;
      if (((local_20 & 1) == 0) || ((D3IniFlags & 0x200000U) != 0)) goto LAB_005426dd;
      local_10 = 0;
      local_18 = param_3 + param_4 + -1;
      if (0 < param_4) {
        local_8 = &(pPVar7->Texel).field2_0x8;
        local_c = pPVar7 + 1;
        local_1c = param_4;
        pPVar6 = param_3 + param_4 + -1;
        do {
          fVar1 = (pPVar6->Vector).z;
          local_18 = pPVar6;
          if (local_24 <= (param_3->Vector).z) {
            if (fVar1 < local_24) {
              ptVar3 = (tagLIGHTING *)
                       ((local_24 - (pPVar6->Vector).z) / ((param_3->Vector).z - (pPVar6->Vector).z)
                       );
              (pPVar7->Vector).z = local_24;
              (pPVar7->Vector).x =
                   ((param_3->Vector).x - (pPVar6->Vector).x) * (float)ptVar3 + (pPVar6->Vector).x;
              (pPVar7->Vector).y =
                   ((param_3->Vector).y - (pPVar6->Vector).y) * (float)ptVar3 + (pPVar6->Vector).y;
              ClipLighting(ptVar3,unaff_EDI,unaff_ESI,unaff_EBX);
              local_14 = local_14 + 1;
              local_c = local_c + 1;
              local_8 = local_8 + 6;
              local_10 = local_10 + 1;
              pPVar7 = local_14;
            }
          }
          else {
            iVar5 = 6;
            pPVar8 = param_3;
            pPVar9 = local_c;
            if (fVar1 < local_24) {
              local_c = local_c + 1;
              local_8 = local_8 + 6;
              local_10 = local_10 + 1;
              pPVar6 = param_3;
              pPVar8 = pPVar7;
              for (; iVar5 != 0; iVar5 = iVar5 + -1) {
                (pPVar8->Vector).x = (pPVar6->Vector).x;
                pPVar6 = (POINT_3D *)&(pPVar6->Vector).y;
                pPVar8 = (POINT_3D *)&(pPVar8->Vector).y;
              }
              local_14 = pPVar7 + 1;
              pPVar7 = pPVar7 + 1;
            }
            else {
              for (; iVar5 != 0; iVar5 = iVar5 + -1) {
                (pPVar9->Vector).x = (pPVar8->Vector).x;
                pPVar8 = (POINT_3D *)&(pPVar8->Vector).y;
                pPVar9 = (POINT_3D *)&(pPVar9->Vector).y;
              }
              ptVar3 = (tagLIGHTING *)
                       ((local_24 - (pPVar6->Vector).z) / ((param_3->Vector).z - (pPVar6->Vector).z)
                       );
              (pPVar7->Vector).z = local_24;
              (pPVar7->Vector).x =
                   ((param_3->Vector).x - (pPVar6->Vector).x) * (float)ptVar3 + (pPVar6->Vector).x;
              (pPVar7->Vector).y =
                   ((param_3->Vector).y - (pPVar6->Vector).y) * (float)ptVar3 + (pPVar6->Vector).y;
              ClipLighting(ptVar3,unaff_EDI,unaff_ESI,unaff_EBX);
              local_14 = local_14 + 2;
              local_c = local_c + 2;
              local_8 = local_8 + 0xc;
              local_10 = local_10 + 2;
              pPVar7 = local_14;
            }
          }
          local_18 = param_3;
          local_1c = local_1c + -1;
          pPVar6 = param_3;
          param_3 = param_3 + 1;
        } while (local_1c != 0);
        if (local_10 != 0) {
          param_3 = pPVar7 + -local_10;
          param_4 = local_10;
          goto LAB_005426dd;
        }
      }
    }
    else {
      local_10 = 0;
      if (0 < param_4) {
        local_8 = &local_68c.Texel.field2_0x8;
        local_c = local_674;
        local_1c = param_4;
        pPVar6 = param_3 + param_4 + -1;
        pPVar8 = param_3;
        do {
          param_3 = pPVar8;
          fVar1 = (param_3->Vector).z;
          fVar2 = (pPVar6->Vector).z;
          local_18 = pPVar6;
          if (local_28 < fVar1 == (local_28 == fVar1)) {
            if (local_28 < fVar2 != (local_28 == fVar2)) {
              ptVar3 = (tagLIGHTING *)
                       ((local_28 - (pPVar6->Vector).z) / ((param_3->Vector).z - (pPVar6->Vector).z)
                       );
              (pPVar7->Vector).z = local_28;
              (pPVar7->Vector).x =
                   ((param_3->Vector).x - (pPVar6->Vector).x) * (float)ptVar3 + (pPVar6->Vector).x;
              (pPVar7->Vector).y =
                   ((param_3->Vector).y - (pPVar6->Vector).y) * (float)ptVar3 + (pPVar6->Vector).y;
              ClipLighting(ptVar3,unaff_EDI,unaff_ESI,unaff_EBX);
              local_14 = local_14 + 1;
              local_c = local_c + 1;
              local_8 = local_8 + 6;
              local_10 = local_10 + 1;
              pPVar7 = local_14;
            }
          }
          else {
            iVar5 = 6;
            if (local_28 < fVar2 == (local_28 == fVar2)) {
              fVar1 = (pPVar6->Vector).z;
              fVar2 = (param_3->Vector).z;
              pPVar8 = param_3;
              pPVar9 = local_c;
              for (; iVar5 != 0; iVar5 = iVar5 + -1) {
                (pPVar9->Vector).x = (pPVar8->Vector).x;
                pPVar8 = (POINT_3D *)&(pPVar8->Vector).y;
                pPVar9 = (POINT_3D *)&(pPVar9->Vector).y;
              }
              ptVar3 = (tagLIGHTING *)((local_28 - fVar1) / (fVar2 - (pPVar6->Vector).z));
              (pPVar7->Vector).z = local_28;
              (pPVar7->Vector).x =
                   ((param_3->Vector).x - (pPVar6->Vector).x) * (float)ptVar3 + (pPVar6->Vector).x;
              (pPVar7->Vector).y =
                   ((param_3->Vector).y - (pPVar6->Vector).y) * (float)ptVar3 + (pPVar6->Vector).y;
              ClipLighting(ptVar3,unaff_EDI,unaff_ESI,unaff_EBX);
              local_14 = local_14 + 2;
              local_c = local_c + 2;
              local_8 = local_8 + 0xc;
              local_10 = local_10 + 2;
              pPVar7 = local_14;
            }
            else {
              local_c = local_c + 1;
              local_8 = local_8 + 6;
              local_10 = local_10 + 1;
              pPVar6 = param_3;
              pPVar8 = pPVar7;
              for (; iVar5 != 0; iVar5 = iVar5 + -1) {
                (pPVar8->Vector).x = (pPVar6->Vector).x;
                pPVar6 = (POINT_3D *)&(pPVar6->Vector).y;
                pPVar8 = (POINT_3D *)&(pPVar8->Vector).y;
              }
              local_14 = pPVar7 + 1;
              pPVar7 = pPVar7 + 1;
            }
          }
          local_1c = local_1c + -1;
          pPVar6 = param_3;
          pPVar8 = param_3 + 1;
        } while (local_1c != 0);
        if (local_10 != 0) {
          local_1c = 0;
          param_4 = local_10;
          pPVar6 = pPVar7 + -local_10;
          local_18 = param_3;
          goto LAB_005424c8;
        }
      }
    }
    lVar4 = 0;
  }
  return lVar4;
}
