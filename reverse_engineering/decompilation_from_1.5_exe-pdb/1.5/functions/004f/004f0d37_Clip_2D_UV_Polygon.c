/*
 * Entry: 004f0d37
 * Name: __Clip_2D_UV_Polygon
 * Namespace: Global
 * Signature: long __Clip_2D_UV_Polygon(CAMERA * param_1, POINT_3D * param_2, POINT_3D * param_3, long param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl
__Clip_2D_UV_Polygon(CAMERA *param_1,POINT_3D *param_2,POINT_3D *param_3,long param_4,long param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  POINT_3D *pPVar5;
  float *pfVar6;
  POINT_3D *pPVar7;
  POINT_3D *pPVar8;
  float *pfVar9;
  float *pfVar10;
  float local_cac [6];
  float local_c94 [798];
  int local_1c;
  uint local_18;
  int local_14;
  POINT_3D *local_10;
  float *local_c;
  int local_8;
  
  Compute_Outcode(&local_1c,(long *)&local_18,param_3,param_4,param_1);
  if (local_1c != 0) {
    return 0;
  }
  if (local_18 != 0) {
    pfVar6 = local_cac;
    if ((local_18 & 8) != 0) {
      local_8 = 0;
      if (param_4 < 1) {
        return 0;
      }
      local_c = local_c94;
      local_14 = param_4;
      pPVar5 = param_3 + param_4 + -1;
      do {
        pPVar8 = param_3;
        fVar1 = (pPVar8->Vector).x;
        fVar2 = param_1->Left;
        fVar3 = (pPVar5->Vector).x;
        if (param_1->Left < fVar1 == (param_1->Left == fVar1)) {
          if (fVar2 < fVar3 != (fVar2 == fVar3)) {
            fVar1 = (param_1->Left - (pPVar5->Vector).x) / ((pPVar8->Vector).x - (pPVar5->Vector).x)
            ;
            *pfVar6 = param_1->Left;
            pfVar6[1] = ((pPVar8->Vector).y - (pPVar5->Vector).y) * fVar1 + (pPVar5->Vector).y;
            pfVar6[2] = ((pPVar8->Vector).z - (pPVar5->Vector).z) * fVar1 + (pPVar5->Vector).z;
            pfVar6[3] = ((pPVar8->Texel).u - (pPVar5->Texel).u) * fVar1 + (pPVar5->Texel).u;
            pfVar6[4] = ((pPVar8->Texel).v - (pPVar5->Texel).v) * fVar1 + (pPVar5->Texel).v;
            pfVar6[5] = ((pPVar8->Texel).field2_0x8.luma - (pPVar5->Texel).field2_0x8.luma) * fVar1
                        + (pPVar5->Texel).field2_0x8.luma;
            goto LAB_004f0ea3;
          }
        }
        else {
          iVar4 = 6;
          pPVar7 = pPVar8;
          pfVar10 = local_c;
          pfVar9 = pfVar6;
          if (fVar2 < fVar3 == (fVar2 == fVar3)) {
            for (; iVar4 != 0; iVar4 = iVar4 + -1) {
              *pfVar10 = (pPVar7->Vector).x;
              pPVar7 = (POINT_3D *)&(pPVar7->Vector).y;
              pfVar10 = pfVar10 + 1;
            }
            local_c = local_c + 0xc;
            fVar1 = (param_1->Left - (pPVar5->Vector).x) / ((pPVar8->Vector).x - (pPVar5->Vector).x)
            ;
            *pfVar6 = param_1->Left;
            local_8 = local_8 + 2;
            pfVar6[1] = ((pPVar8->Vector).y - (pPVar5->Vector).y) * fVar1 + (pPVar5->Vector).y;
            pfVar6[2] = ((pPVar8->Vector).z - (pPVar5->Vector).z) * fVar1 + (pPVar5->Vector).z;
            pfVar6[3] = ((pPVar8->Texel).u - (pPVar5->Texel).u) * fVar1 + (pPVar5->Texel).u;
            pfVar6[4] = ((pPVar8->Texel).v - (pPVar5->Texel).v) * fVar1 + (pPVar5->Texel).v;
            pfVar6[5] = ((pPVar8->Texel).field2_0x8.luma - (pPVar5->Texel).field2_0x8.luma) * fVar1
                        + (pPVar5->Texel).field2_0x8.luma;
            pfVar6 = pfVar6 + 0xc;
          }
          else {
            for (; iVar4 != 0; iVar4 = iVar4 + -1) {
              *pfVar9 = (pPVar7->Vector).x;
              pPVar7 = (POINT_3D *)&(pPVar7->Vector).y;
              pfVar9 = pfVar9 + 1;
            }
LAB_004f0ea3:
            local_c = local_c + 6;
            local_8 = local_8 + 1;
            pfVar6 = pfVar6 + 6;
          }
        }
        local_14 = local_14 + -1;
        pPVar5 = pPVar8;
        param_3 = pPVar8 + 1;
      } while (local_14 != 0);
      if (local_8 == 0) {
        return 0;
      }
      param_3 = (POINT_3D *)(pfVar6 + local_8 * -6);
      local_14 = 0;
      param_4 = local_8;
      local_10 = pPVar8;
    }
    if ((local_18 & 2) != 0) {
      local_8 = 0;
      local_10 = param_3 + param_4 + -1;
      if (param_4 < 1) {
        return 0;
      }
      local_c = pfVar6 + 6;
      local_14 = param_4;
      pPVar5 = param_3 + param_4 + -1;
      do {
        fVar1 = (param_3->Vector).y;
        fVar2 = param_1->Bottom;
        fVar3 = (pPVar5->Vector).y;
        if (param_1->Bottom < fVar1 == (param_1->Bottom == fVar1)) {
          if (fVar2 < fVar3 != (fVar2 == fVar3)) {
            fVar1 = (param_1->Bottom - (pPVar5->Vector).y) /
                    ((param_3->Vector).y - (pPVar5->Vector).y);
            pfVar6[1] = param_1->Bottom;
            *pfVar6 = ((param_3->Vector).x - (pPVar5->Vector).x) * fVar1 + (pPVar5->Vector).x;
            pfVar6[2] = ((param_3->Vector).z - (pPVar5->Vector).z) * fVar1 + (pPVar5->Vector).z;
            pfVar6[3] = ((param_3->Texel).u - (pPVar5->Texel).u) * fVar1 + (pPVar5->Texel).u;
            pfVar6[4] = ((param_3->Texel).v - (pPVar5->Texel).v) * fVar1 + (pPVar5->Texel).v;
            pfVar6[5] = ((param_3->Texel).field2_0x8.luma - (pPVar5->Texel).field2_0x8.luma) * fVar1
                        + (pPVar5->Texel).field2_0x8.luma;
            goto LAB_004f0ffa;
          }
        }
        else {
          iVar4 = 6;
          pPVar8 = param_3;
          pfVar10 = local_c;
          pfVar9 = pfVar6;
          if (fVar2 < fVar3 == (fVar2 == fVar3)) {
            for (; iVar4 != 0; iVar4 = iVar4 + -1) {
              *pfVar10 = (pPVar8->Vector).x;
              pPVar8 = (POINT_3D *)&(pPVar8->Vector).y;
              pfVar10 = pfVar10 + 1;
            }
            local_c = local_c + 0xc;
            fVar1 = (param_1->Bottom - (pPVar5->Vector).y) /
                    ((param_3->Vector).y - (pPVar5->Vector).y);
            pfVar6[1] = param_1->Bottom;
            *pfVar6 = ((param_3->Vector).x - (pPVar5->Vector).x) * fVar1 + (pPVar5->Vector).x;
            local_8 = local_8 + 2;
            pfVar6[2] = ((param_3->Vector).z - (pPVar5->Vector).z) * fVar1 + (pPVar5->Vector).z;
            pfVar6[3] = ((param_3->Texel).u - (pPVar5->Texel).u) * fVar1 + (pPVar5->Texel).u;
            pfVar6[4] = ((param_3->Texel).v - (pPVar5->Texel).v) * fVar1 + (pPVar5->Texel).v;
            pfVar6[5] = ((param_3->Texel).field2_0x8.luma - (pPVar5->Texel).field2_0x8.luma) * fVar1
                        + (pPVar5->Texel).field2_0x8.luma;
            pfVar6 = pfVar6 + 0xc;
          }
          else {
            for (; iVar4 != 0; iVar4 = iVar4 + -1) {
              *pfVar9 = (pPVar8->Vector).x;
              pPVar8 = (POINT_3D *)&(pPVar8->Vector).y;
              pfVar9 = pfVar9 + 1;
            }
LAB_004f0ffa:
            local_c = local_c + 6;
            local_8 = local_8 + 1;
            pfVar6 = pfVar6 + 6;
          }
        }
        local_10 = param_3;
        local_14 = local_14 + -1;
        pPVar5 = param_3;
        param_3 = param_3 + 1;
      } while (local_14 != 0);
      if (local_8 == 0) {
        return 0;
      }
      param_3 = (POINT_3D *)(pfVar6 + local_8 * -6);
      param_4 = local_8;
    }
    if ((local_18 & 4) != 0) {
      local_8 = 0;
      local_10 = param_3 + param_4 + -1;
      if (param_4 < 1) {
        return 0;
      }
      local_c = pfVar6 + 6;
      local_14 = param_4;
      pPVar5 = param_3 + param_4 + -1;
      do {
        fVar1 = (pPVar5->Vector).x;
        if (param_1->Right <= (param_3->Vector).x) {
          if (fVar1 < param_1->Right) {
            fVar1 = (param_1->Right - (pPVar5->Vector).x) /
                    ((param_3->Vector).x - (pPVar5->Vector).x);
            *pfVar6 = param_1->Right;
            pfVar6[1] = ((param_3->Vector).y - (pPVar5->Vector).y) * fVar1 + (pPVar5->Vector).y;
            pfVar6[2] = ((param_3->Vector).z - (pPVar5->Vector).z) * fVar1 + (pPVar5->Vector).z;
            pfVar6[3] = ((param_3->Texel).u - (pPVar5->Texel).u) * fVar1 + (pPVar5->Texel).u;
            pfVar6[4] = ((param_3->Texel).v - (pPVar5->Texel).v) * fVar1 + (pPVar5->Texel).v;
            pfVar6[5] = ((param_3->Texel).field2_0x8.luma - (pPVar5->Texel).field2_0x8.luma) * fVar1
                        + (pPVar5->Texel).field2_0x8.luma;
            goto LAB_004f114f;
          }
        }
        else {
          iVar4 = 6;
          pPVar8 = param_3;
          pfVar10 = local_c;
          pfVar9 = pfVar6;
          if (param_1->Right <= fVar1) {
            for (; iVar4 != 0; iVar4 = iVar4 + -1) {
              *pfVar10 = (pPVar8->Vector).x;
              pPVar8 = (POINT_3D *)&(pPVar8->Vector).y;
              pfVar10 = pfVar10 + 1;
            }
            local_c = local_c + 0xc;
            fVar1 = (param_1->Right - (pPVar5->Vector).x) /
                    ((param_3->Vector).x - (pPVar5->Vector).x);
            *pfVar6 = param_1->Right;
            local_8 = local_8 + 2;
            pfVar6[1] = ((param_3->Vector).y - (pPVar5->Vector).y) * fVar1 + (pPVar5->Vector).y;
            pfVar6[2] = ((param_3->Vector).z - (pPVar5->Vector).z) * fVar1 + (pPVar5->Vector).z;
            pfVar6[3] = ((param_3->Texel).u - (pPVar5->Texel).u) * fVar1 + (pPVar5->Texel).u;
            pfVar6[4] = ((param_3->Texel).v - (pPVar5->Texel).v) * fVar1 + (pPVar5->Texel).v;
            pfVar6[5] = ((param_3->Texel).field2_0x8.luma - (pPVar5->Texel).field2_0x8.luma) * fVar1
                        + (pPVar5->Texel).field2_0x8.luma;
            pfVar6 = pfVar6 + 0xc;
          }
          else {
            for (; iVar4 != 0; iVar4 = iVar4 + -1) {
              *pfVar9 = (pPVar8->Vector).x;
              pPVar8 = (POINT_3D *)&(pPVar8->Vector).y;
              pfVar9 = pfVar9 + 1;
            }
LAB_004f114f:
            local_c = local_c + 6;
            local_8 = local_8 + 1;
            pfVar6 = pfVar6 + 6;
          }
        }
        local_10 = param_3;
        local_14 = local_14 + -1;
        pPVar5 = param_3;
        param_3 = param_3 + 1;
      } while (local_14 != 0);
      if (local_8 == 0) {
        return 0;
      }
      param_3 = (POINT_3D *)(pfVar6 + local_8 * -6);
      param_4 = local_8;
    }
    if ((local_18 & 1) != 0) {
      local_8 = 0;
      local_10 = param_3 + param_4 + -1;
      if (0 < param_4) {
        local_c = pfVar6 + 6;
        local_14 = param_4;
        pPVar5 = param_3 + param_4 + -1;
        do {
          fVar1 = (pPVar5->Vector).y;
          if (param_1->Top <= (param_3->Vector).y) {
            if (fVar1 < param_1->Top) {
              fVar1 = (param_1->Top - (pPVar5->Vector).y) /
                      ((param_3->Vector).y - (pPVar5->Vector).y);
              pfVar6[1] = param_1->Top;
              *pfVar6 = ((param_3->Vector).x - (pPVar5->Vector).x) * fVar1 + (pPVar5->Vector).x;
              pfVar6[2] = ((param_3->Vector).z - (pPVar5->Vector).z) * fVar1 + (pPVar5->Vector).z;
              pfVar6[3] = ((param_3->Texel).u - (pPVar5->Texel).u) * fVar1 + (pPVar5->Texel).u;
              pfVar6[4] = ((param_3->Texel).v - (pPVar5->Texel).v) * fVar1 + (pPVar5->Texel).v;
              pfVar6[5] = ((param_3->Texel).field2_0x8.luma - (pPVar5->Texel).field2_0x8.luma) *
                          fVar1 + (pPVar5->Texel).field2_0x8.luma;
              goto LAB_004f12a6;
            }
          }
          else {
            iVar4 = 6;
            pPVar8 = param_3;
            pfVar10 = local_c;
            pfVar9 = pfVar6;
            if (param_1->Top <= fVar1) {
              for (; iVar4 != 0; iVar4 = iVar4 + -1) {
                *pfVar10 = (pPVar8->Vector).x;
                pPVar8 = (POINT_3D *)&(pPVar8->Vector).y;
                pfVar10 = pfVar10 + 1;
              }
              local_c = local_c + 0xc;
              fVar1 = (param_1->Top - (pPVar5->Vector).y) /
                      ((param_3->Vector).y - (pPVar5->Vector).y);
              pfVar6[1] = param_1->Top;
              *pfVar6 = ((param_3->Vector).x - (pPVar5->Vector).x) * fVar1 + (pPVar5->Vector).x;
              local_8 = local_8 + 2;
              pfVar6[2] = ((param_3->Vector).z - (pPVar5->Vector).z) * fVar1 + (pPVar5->Vector).z;
              pfVar6[3] = ((param_3->Texel).u - (pPVar5->Texel).u) * fVar1 + (pPVar5->Texel).u;
              pfVar6[4] = ((param_3->Texel).v - (pPVar5->Texel).v) * fVar1 + (pPVar5->Texel).v;
              pfVar6[5] = ((param_3->Texel).field2_0x8.luma - (pPVar5->Texel).field2_0x8.luma) *
                          fVar1 + (pPVar5->Texel).field2_0x8.luma;
              pfVar6 = pfVar6 + 0xc;
            }
            else {
              for (; iVar4 != 0; iVar4 = iVar4 + -1) {
                *pfVar9 = (pPVar8->Vector).x;
                pPVar8 = (POINT_3D *)&(pPVar8->Vector).y;
                pfVar9 = pfVar9 + 1;
              }
LAB_004f12a6:
              local_c = local_c + 6;
              local_8 = local_8 + 1;
              pfVar6 = pfVar6 + 6;
            }
          }
          local_10 = param_3;
          local_14 = local_14 + -1;
          pPVar5 = param_3;
          param_3 = param_3 + 1;
        } while (local_14 != 0);
        if (local_8 != 0) {
          param_3 = (POINT_3D *)(pfVar6 + local_8 * -6);
          param_4 = local_8;
          goto LAB_004f12d3;
        }
      }
      return 0;
    }
  }
LAB_004f12d3:
  memmove(param_2,param_3,param_4 * 0x18);
  return param_4;
}
