/*
 * Entry: 0054141c
 * Name: D3D_Clip_2D_Polygon
 * Namespace: Global
 * Signature: long D3D_Clip_2D_Polygon(CAMERA * param_1, POINT_3D * param_2, POINT_3D * param_3, long param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl
D3D_Clip_2D_Polygon(CAMERA *param_1,POINT_3D *param_2,POINT_3D *param_3,long param_4,long param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  tagLIGHTING *ptVar4;
  int iVar5;
  POINT_3D *pPVar6;
  float *pfVar7;
  float *pfVar8;
  float unaff_EBX;
  tagLIGHTING *unaff_ESI;
  POINT_3D *pPVar9;
  tagLIGHTING *unaff_EDI;
  float local_cb4 [5];
  float local_ca0;
  float local_c9c [798];
  int local_24;
  uint local_20;
  int local_1c;
  POINT_3D *local_18;
  float *local_14;
  int local_10;
  float *local_c;
  float *local_8;
  
  Compute_Outcode(&local_24,(long *)&local_20,param_3,param_4,param_1);
  if (local_24 != 0) {
    return 0;
  }
  if ((local_20 != 0) && ((D3IniFlags & 0x200000U) == 0)) {
    pfVar8 = local_cb4;
    local_14 = pfVar8;
    pPVar6 = param_3;
    if ((local_20 & 8) != 0) {
      local_10 = 0;
      if (param_4 < 1) {
        return 0;
      }
      local_8 = &local_ca0;
      local_c = local_c9c;
      local_1c = param_4;
      pPVar6 = param_3 + param_4 + -1;
      pPVar9 = param_3;
      do {
        param_3 = pPVar9;
        fVar1 = (param_3->Vector).x;
        fVar2 = param_1->Left;
        fVar3 = (pPVar6->Vector).x;
        local_18 = pPVar6;
        if (param_1->Left < fVar1 == (param_1->Left == fVar1)) {
          if (fVar2 < fVar3 != (fVar2 == fVar3)) {
            ptVar4 = (tagLIGHTING *)
                     ((param_1->Left - (pPVar6->Vector).x) /
                     ((param_3->Vector).x - (pPVar6->Vector).x));
            *pfVar8 = param_1->Left;
            pfVar8[1] = ((param_3->Vector).y - (pPVar6->Vector).y) * (float)ptVar4 +
                        (pPVar6->Vector).y;
            pfVar8[2] = ((param_3->Vector).z - (pPVar6->Vector).z) * (float)ptVar4 +
                        (pPVar6->Vector).z;
            ClipLighting(ptVar4,unaff_EDI,unaff_ESI,unaff_EBX);
            pfVar7 = local_14 + 6;
            local_14 = pfVar7;
            goto LAB_00541588;
          }
        }
        else {
          iVar5 = 6;
          pPVar9 = param_3;
          pfVar7 = local_c;
          if (fVar2 < fVar3 == (fVar2 == fVar3)) {
            for (; iVar5 != 0; iVar5 = iVar5 + -1) {
              *pfVar7 = (pPVar9->Vector).x;
              pPVar9 = (POINT_3D *)&(pPVar9->Vector).y;
              pfVar7 = pfVar7 + 1;
            }
            ptVar4 = (tagLIGHTING *)
                     ((param_1->Left - (pPVar6->Vector).x) /
                     ((param_3->Vector).x - (pPVar6->Vector).x));
            *pfVar8 = param_1->Left;
            pfVar8[1] = ((param_3->Vector).y - (pPVar6->Vector).y) * (float)ptVar4 +
                        (pPVar6->Vector).y;
            pfVar8[2] = ((param_3->Vector).z - (pPVar6->Vector).z) * (float)ptVar4 +
                        (pPVar6->Vector).z;
            ClipLighting(ptVar4,unaff_EDI,unaff_ESI,unaff_EBX);
            local_14 = local_14 + 0xc;
            local_c = local_c + 0xc;
            local_8 = local_8 + 0xc;
            local_10 = local_10 + 2;
            pfVar8 = local_14;
          }
          else {
            pfVar7 = pfVar8 + 6;
            pPVar6 = param_3;
            for (; iVar5 != 0; iVar5 = iVar5 + -1) {
              *pfVar8 = (pPVar6->Vector).x;
              pPVar6 = (POINT_3D *)&(pPVar6->Vector).y;
              pfVar8 = pfVar8 + 1;
            }
            local_14 = pfVar7;
LAB_00541588:
            local_c = local_c + 6;
            local_8 = local_8 + 6;
            local_10 = local_10 + 1;
            pfVar8 = pfVar7;
            local_14 = pfVar7;
          }
        }
        local_1c = local_1c + -1;
        pPVar6 = param_3;
        pPVar9 = param_3 + 1;
      } while (local_1c != 0);
      if (local_10 == 0) {
        return 0;
      }
      local_1c = 0;
      param_4 = local_10;
      pPVar6 = (POINT_3D *)(pfVar8 + local_10 * -6);
      local_18 = param_3;
    }
    param_3 = pPVar6;
    if ((local_20 & 2) != 0) {
      local_10 = 0;
      local_18 = param_3 + param_4 + -1;
      if (param_4 < 1) {
        return 0;
      }
      local_8 = pfVar8 + 5;
      local_c = pfVar8 + 6;
      local_1c = param_4;
      pPVar6 = param_3 + param_4 + -1;
      do {
        fVar1 = (param_3->Vector).y;
        fVar2 = param_1->Bottom;
        fVar3 = (pPVar6->Vector).y;
        local_18 = pPVar6;
        if (param_1->Bottom < fVar1 == (param_1->Bottom == fVar1)) {
          if (fVar2 < fVar3 != (fVar2 == fVar3)) {
            ptVar4 = (tagLIGHTING *)
                     ((param_1->Bottom - (pPVar6->Vector).y) /
                     ((param_3->Vector).y - (pPVar6->Vector).y));
            pfVar8[1] = param_1->Bottom;
            *pfVar8 = ((param_3->Vector).x - (pPVar6->Vector).x) * (float)ptVar4 +
                      (pPVar6->Vector).x;
            pfVar8[2] = ((param_3->Vector).z - (pPVar6->Vector).z) * (float)ptVar4 +
                        (pPVar6->Vector).z;
            ClipLighting(ptVar4,unaff_EDI,unaff_ESI,unaff_EBX);
            pfVar7 = local_14 + 6;
            local_14 = pfVar7;
            goto LAB_005416d5;
          }
        }
        else {
          iVar5 = 6;
          pPVar9 = param_3;
          pfVar7 = local_c;
          if (fVar2 < fVar3 == (fVar2 == fVar3)) {
            for (; iVar5 != 0; iVar5 = iVar5 + -1) {
              *pfVar7 = (pPVar9->Vector).x;
              pPVar9 = (POINT_3D *)&(pPVar9->Vector).y;
              pfVar7 = pfVar7 + 1;
            }
            ptVar4 = (tagLIGHTING *)
                     ((param_1->Bottom - (pPVar6->Vector).y) /
                     ((param_3->Vector).y - (pPVar6->Vector).y));
            pfVar8[1] = param_1->Bottom;
            *pfVar8 = ((param_3->Vector).x - (pPVar6->Vector).x) * (float)ptVar4 +
                      (pPVar6->Vector).x;
            pfVar8[2] = ((param_3->Vector).z - (pPVar6->Vector).z) * (float)ptVar4 +
                        (pPVar6->Vector).z;
            ClipLighting(ptVar4,unaff_EDI,unaff_ESI,unaff_EBX);
            local_14 = local_14 + 0xc;
            local_c = local_c + 0xc;
            local_8 = local_8 + 0xc;
            local_10 = local_10 + 2;
            pfVar8 = local_14;
          }
          else {
            pfVar7 = pfVar8 + 6;
            pPVar6 = param_3;
            for (; iVar5 != 0; iVar5 = iVar5 + -1) {
              *pfVar8 = (pPVar6->Vector).x;
              pPVar6 = (POINT_3D *)&(pPVar6->Vector).y;
              pfVar8 = pfVar8 + 1;
            }
            local_14 = pfVar7;
LAB_005416d5:
            local_c = local_c + 6;
            local_8 = local_8 + 6;
            local_10 = local_10 + 1;
            pfVar8 = pfVar7;
            local_14 = pfVar7;
          }
        }
        local_18 = param_3;
        local_1c = local_1c + -1;
        pPVar6 = param_3;
        param_3 = param_3 + 1;
      } while (local_1c != 0);
      if (local_10 == 0) {
        return 0;
      }
      param_3 = (POINT_3D *)(pfVar8 + local_10 * -6);
      param_4 = local_10;
    }
    if ((local_20 & 4) != 0) {
      local_10 = 0;
      local_18 = param_3 + param_4 + -1;
      if (param_4 < 1) {
        return 0;
      }
      local_8 = pfVar8 + 5;
      local_c = pfVar8 + 6;
      local_1c = param_4;
      pPVar6 = param_3 + param_4 + -1;
      do {
        fVar1 = (pPVar6->Vector).x;
        local_18 = pPVar6;
        if (param_1->Right <= (param_3->Vector).x) {
          if (fVar1 < param_1->Right) {
            ptVar4 = (tagLIGHTING *)
                     ((param_1->Right - (pPVar6->Vector).x) /
                     ((param_3->Vector).x - (pPVar6->Vector).x));
            *pfVar8 = param_1->Right;
            pfVar8[1] = ((param_3->Vector).y - (pPVar6->Vector).y) * (float)ptVar4 +
                        (pPVar6->Vector).y;
            pfVar8[2] = ((param_3->Vector).z - (pPVar6->Vector).z) * (float)ptVar4 +
                        (pPVar6->Vector).z;
            ClipLighting(ptVar4,unaff_EDI,unaff_ESI,unaff_EBX);
            pfVar7 = local_14 + 6;
            local_14 = pfVar7;
            goto LAB_00541820;
          }
        }
        else {
          iVar5 = 6;
          pPVar9 = param_3;
          pfVar7 = local_c;
          if (param_1->Right <= fVar1) {
            for (; iVar5 != 0; iVar5 = iVar5 + -1) {
              *pfVar7 = (pPVar9->Vector).x;
              pPVar9 = (POINT_3D *)&(pPVar9->Vector).y;
              pfVar7 = pfVar7 + 1;
            }
            ptVar4 = (tagLIGHTING *)
                     ((param_1->Right - (pPVar6->Vector).x) /
                     ((param_3->Vector).x - (pPVar6->Vector).x));
            *pfVar8 = param_1->Right;
            pfVar8[1] = ((param_3->Vector).y - (pPVar6->Vector).y) * (float)ptVar4 +
                        (pPVar6->Vector).y;
            pfVar8[2] = ((param_3->Vector).z - (pPVar6->Vector).z) * (float)ptVar4 +
                        (pPVar6->Vector).z;
            ClipLighting(ptVar4,unaff_EDI,unaff_ESI,unaff_EBX);
            local_14 = local_14 + 0xc;
            local_c = local_c + 0xc;
            local_8 = local_8 + 0xc;
            local_10 = local_10 + 2;
            pfVar8 = local_14;
          }
          else {
            pfVar7 = pfVar8 + 6;
            pPVar6 = param_3;
            for (; iVar5 != 0; iVar5 = iVar5 + -1) {
              *pfVar8 = (pPVar6->Vector).x;
              pPVar6 = (POINT_3D *)&(pPVar6->Vector).y;
              pfVar8 = pfVar8 + 1;
            }
            local_14 = pfVar7;
LAB_00541820:
            local_c = local_c + 6;
            local_8 = local_8 + 6;
            local_10 = local_10 + 1;
            pfVar8 = pfVar7;
            local_14 = pfVar7;
          }
        }
        local_18 = param_3;
        local_1c = local_1c + -1;
        pPVar6 = param_3;
        param_3 = param_3 + 1;
      } while (local_1c != 0);
      if (local_10 == 0) {
        return 0;
      }
      param_3 = (POINT_3D *)(pfVar8 + local_10 * -6);
      param_4 = local_10;
    }
    if ((local_20 & 1) != 0) {
      local_10 = 0;
      local_18 = param_3 + param_4 + -1;
      if (0 < param_4) {
        local_8 = pfVar8 + 5;
        local_c = pfVar8 + 6;
        local_1c = param_4;
        pPVar6 = param_3 + param_4 + -1;
        do {
          fVar1 = (pPVar6->Vector).y;
          local_18 = pPVar6;
          if (param_1->Top <= (param_3->Vector).y) {
            if (fVar1 < param_1->Top) {
              ptVar4 = (tagLIGHTING *)
                       ((param_1->Top - (pPVar6->Vector).y) /
                       ((param_3->Vector).y - (pPVar6->Vector).y));
              pfVar8[1] = param_1->Top;
              *pfVar8 = ((param_3->Vector).x - (pPVar6->Vector).x) * (float)ptVar4 +
                        (pPVar6->Vector).x;
              pfVar8[2] = ((param_3->Vector).z - (pPVar6->Vector).z) * (float)ptVar4 +
                          (pPVar6->Vector).z;
              ClipLighting(ptVar4,unaff_EDI,unaff_ESI,unaff_EBX);
              pfVar7 = local_14 + 6;
              local_14 = pfVar7;
              goto LAB_0054196d;
            }
          }
          else {
            iVar5 = 6;
            pPVar9 = param_3;
            pfVar7 = local_c;
            if (param_1->Top <= fVar1) {
              for (; iVar5 != 0; iVar5 = iVar5 + -1) {
                *pfVar7 = (pPVar9->Vector).x;
                pPVar9 = (POINT_3D *)&(pPVar9->Vector).y;
                pfVar7 = pfVar7 + 1;
              }
              ptVar4 = (tagLIGHTING *)
                       ((param_1->Top - (pPVar6->Vector).y) /
                       ((param_3->Vector).y - (pPVar6->Vector).y));
              pfVar8[1] = param_1->Top;
              *pfVar8 = ((param_3->Vector).x - (pPVar6->Vector).x) * (float)ptVar4 +
                        (pPVar6->Vector).x;
              pfVar8[2] = ((param_3->Vector).z - (pPVar6->Vector).z) * (float)ptVar4 +
                          (pPVar6->Vector).z;
              ClipLighting(ptVar4,unaff_EDI,unaff_ESI,unaff_EBX);
              local_14 = local_14 + 0xc;
              local_c = local_c + 0xc;
              local_8 = local_8 + 0xc;
              local_10 = local_10 + 2;
              pfVar8 = local_14;
            }
            else {
              pfVar7 = pfVar8 + 6;
              pPVar6 = param_3;
              for (; iVar5 != 0; iVar5 = iVar5 + -1) {
                *pfVar8 = (pPVar6->Vector).x;
                pPVar6 = (POINT_3D *)&(pPVar6->Vector).y;
                pfVar8 = pfVar8 + 1;
              }
              local_14 = pfVar7;
LAB_0054196d:
              local_c = local_c + 6;
              local_8 = local_8 + 6;
              local_10 = local_10 + 1;
              pfVar8 = pfVar7;
              local_14 = pfVar7;
            }
          }
          local_18 = param_3;
          local_1c = local_1c + -1;
          pPVar6 = param_3;
          param_3 = param_3 + 1;
        } while (local_1c != 0);
        if (local_10 != 0) {
          param_3 = (POINT_3D *)(pfVar8 + local_10 * -6);
          param_4 = local_10;
          goto LAB_005419a4;
        }
      }
      return 0;
    }
  }
LAB_005419a4:
  memmove(param_2,param_3,param_4 * 0x18);
  return param_4;
}
