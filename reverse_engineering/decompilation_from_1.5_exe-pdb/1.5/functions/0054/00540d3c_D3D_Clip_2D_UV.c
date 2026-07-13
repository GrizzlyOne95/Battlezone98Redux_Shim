/*
 * Entry: 00540d3c
 * Name: D3D_Clip_2D_UV
 * Namespace: Global
 * Signature: long D3D_Clip_2D_UV(CAMERA * param_1, POINT_3D * param_2, long param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl D3D_Clip_2D_UV(CAMERA *param_1,POINT_3D *param_2,long param_3,long param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  tagLIGHTING *ptVar4;
  TEXEL *pTVar5;
  long lVar6;
  float *pfVar7;
  int iVar8;
  POINT_3D *pPVar9;
  float *pfVar10;
  float unaff_EBX;
  POINT_3D *pPVar11;
  tagLIGHTING *unaff_ESI;
  POINT_3D *pPVar12;
  tagLIGHTING *unaff_EDI;
  float local_cb8 [5];
  POINT_3D local_ca4 [133];
  int local_28;
  uint local_24;
  int local_20;
  POINT_3D *local_1c;
  POINT_3D *local_18;
  float *local_14;
  float *local_10;
  int local_c;
  float *local_8;
  
  local_18 = param_2;
  Compute_Outcode(&local_28,(long *)&local_24,param_2,param_3,param_1);
  if (local_28 != 0) {
    return 0;
  }
  if (local_24 == 0) {
    return param_3;
  }
  if ((D3IniFlags & 0x200000U) != 0) {
    return param_3;
  }
  if (0 < param_3) {
    pTVar5 = &param_2->Texel;
    lVar6 = param_3;
    do {
      fVar1 = (((POINT_3D *)(pTVar5 + -1))->Vector).z;
      lVar6 = lVar6 + -1;
      pTVar5->u = fVar1 * pTVar5->u;
      pTVar5->v = fVar1 * pTVar5->v;
      pTVar5 = pTVar5 + 2;
    } while (0 < lVar6);
  }
  pfVar10 = local_cb8;
  local_14 = pfVar10;
  pPVar11 = param_2;
  if ((local_24 & 8) != 0) {
    local_c = 0;
    if (param_3 < 1) {
      return 0;
    }
    local_1c = local_ca4;
    pfVar7 = &(param_2->Vector).z;
    local_8 = &local_ca4[0].Vector.y;
    local_20 = param_3;
    pPVar11 = param_2 + param_3 + -1;
    do {
      local_18 = (POINT_3D *)(pfVar7 + -2);
      fVar1 = (local_18->Vector).x;
      fVar2 = param_1->Left;
      fVar3 = (pPVar11->Vector).x;
      local_10 = pfVar7;
      if (param_1->Left < fVar1 == (param_1->Left == fVar1)) {
        if (fVar2 < fVar3 != (fVar2 == fVar3)) {
          ptVar4 = (tagLIGHTING *)
                   ((param_1->Left - (pPVar11->Vector).x) /
                   ((local_18->Vector).x - (pPVar11->Vector).x));
          *pfVar10 = param_1->Left;
          pfVar10[1] = (pfVar7[-1] - (pPVar11->Vector).y) * (float)ptVar4 + (pPVar11->Vector).y;
          pfVar10[2] = (*pfVar7 - (pPVar11->Vector).z) * (float)ptVar4 + (pPVar11->Vector).z;
          pfVar10[3] = (pfVar7[1] - (pPVar11->Texel).u) * (float)ptVar4 + (pPVar11->Texel).u;
          pfVar10[4] = (pfVar7[2] - (pPVar11->Texel).v) * (float)ptVar4 + (pPVar11->Texel).v;
          ClipLighting(ptVar4,unaff_EDI,unaff_ESI,unaff_EBX);
          pfVar7 = local_14 + 6;
          local_14 = pfVar7;
          goto LAB_00540f0a;
        }
      }
      else {
        iVar8 = 6;
        if (fVar2 < fVar3 == (fVar2 == fVar3)) {
          fVar1 = param_1->Left;
          fVar2 = (pPVar11->Vector).x;
          pPVar9 = local_18;
          pfVar7 = local_8;
          for (; iVar8 != 0; iVar8 = iVar8 + -1) {
            *pfVar7 = (pPVar9->Vector).x;
            pPVar9 = (POINT_3D *)&(pPVar9->Vector).y;
            pfVar7 = pfVar7 + 1;
          }
          ptVar4 = (tagLIGHTING *)((fVar1 - fVar2) / ((local_18->Vector).x - (pPVar11->Vector).x));
          *pfVar10 = param_1->Left;
          pfVar7 = local_10;
          pfVar10[1] = (local_10[-1] - (pPVar11->Vector).y) * (float)ptVar4 + (pPVar11->Vector).y;
          pfVar10[2] = (*pfVar7 - (pPVar11->Vector).z) * (float)ptVar4 + (pPVar11->Vector).z;
          pfVar10[3] = (pfVar7[1] - (pPVar11->Texel).u) * (float)ptVar4 + (pPVar11->Texel).u;
          pfVar10[4] = (pfVar7[2] - (pPVar11->Texel).v) * (float)ptVar4 + (pPVar11->Texel).v;
          ClipLighting(ptVar4,unaff_EDI,unaff_ESI,unaff_EBX);
          local_14 = local_14 + 0xc;
          local_8 = local_8 + 0xc;
          local_1c = local_1c + 2;
          local_c = local_c + 2;
          pfVar10 = local_14;
        }
        else {
          pfVar7 = pfVar10 + 6;
          pPVar11 = local_18;
          for (; iVar8 != 0; iVar8 = iVar8 + -1) {
            *pfVar10 = (pPVar11->Vector).x;
            pPVar11 = (POINT_3D *)&(pPVar11->Vector).y;
            pfVar10 = pfVar10 + 1;
          }
          local_14 = pfVar7;
LAB_00540f0a:
          local_8 = local_8 + 6;
          local_1c = local_1c + 1;
          local_c = local_c + 1;
          pfVar10 = pfVar7;
          local_14 = pfVar7;
        }
      }
      pfVar7 = local_10 + 6;
      local_20 = local_20 + -1;
      pPVar11 = local_18;
    } while (local_20 != 0);
    if (local_c == 0) {
      return 0;
    }
    pPVar11 = (POINT_3D *)(pfVar10 + local_c * -6);
    local_18 = pPVar11;
    local_20 = 0;
    param_3 = local_c;
    local_10 = pfVar7;
  }
  if ((local_24 & 2) != 0) {
    local_c = 0;
    pPVar9 = pPVar11 + param_3 + -1;
    local_1c = pPVar9;
    if (param_3 < 1) {
      return 0;
    }
    local_8 = pfVar10 + 5;
    local_10 = pfVar10 + 6;
    local_20 = param_3;
    do {
      fVar1 = (pPVar11->Vector).y;
      fVar2 = param_1->Bottom;
      fVar3 = (pPVar9->Vector).y;
      local_1c = pPVar9;
      if (param_1->Bottom < fVar1 == (param_1->Bottom == fVar1)) {
        if (fVar2 < fVar3 != (fVar2 == fVar3)) {
          ptVar4 = (tagLIGHTING *)
                   ((param_1->Bottom - (pPVar9->Vector).y) /
                   ((pPVar11->Vector).y - (pPVar9->Vector).y));
          pfVar10[1] = param_1->Bottom;
          *pfVar10 = ((pPVar11->Vector).x - (pPVar9->Vector).x) * (float)ptVar4 + (pPVar9->Vector).x
          ;
          pfVar10[2] = ((pPVar11->Vector).z - (pPVar9->Vector).z) * (float)ptVar4 +
                       (pPVar9->Vector).z;
          pfVar10[3] = ((pPVar11->Texel).u - (pPVar9->Texel).u) * (float)ptVar4 + (pPVar9->Texel).u;
          pfVar10[4] = ((pPVar11->Texel).v - (pPVar9->Texel).v) * (float)ptVar4 + (pPVar9->Texel).v;
          ClipLighting(ptVar4,unaff_EDI,unaff_ESI,unaff_EBX);
          pfVar7 = local_14 + 6;
          local_14 = pfVar7;
          goto LAB_00541096;
        }
      }
      else {
        iVar8 = 6;
        pPVar12 = pPVar11;
        pfVar7 = local_10;
        if (fVar2 < fVar3 == (fVar2 == fVar3)) {
          for (; iVar8 != 0; iVar8 = iVar8 + -1) {
            *pfVar7 = (pPVar12->Vector).x;
            pPVar12 = (POINT_3D *)&(pPVar12->Vector).y;
            pfVar7 = pfVar7 + 1;
          }
          ptVar4 = (tagLIGHTING *)
                   ((param_1->Bottom - (pPVar9->Vector).y) /
                   ((pPVar11->Vector).y - (pPVar9->Vector).y));
          pfVar10[1] = param_1->Bottom;
          *pfVar10 = ((pPVar11->Vector).x - (pPVar9->Vector).x) * (float)ptVar4 + (pPVar9->Vector).x
          ;
          pfVar10[2] = ((pPVar11->Vector).z - (pPVar9->Vector).z) * (float)ptVar4 +
                       (pPVar9->Vector).z;
          pfVar10[3] = ((pPVar11->Texel).u - (pPVar9->Texel).u) * (float)ptVar4 + (pPVar9->Texel).u;
          pfVar10[4] = ((pPVar11->Texel).v - (pPVar9->Texel).v) * (float)ptVar4 + (pPVar9->Texel).v;
          ClipLighting(ptVar4,unaff_EDI,unaff_ESI,unaff_EBX);
          local_14 = local_14 + 0xc;
          local_10 = local_10 + 0xc;
          local_8 = local_8 + 0xc;
          local_c = local_c + 2;
          pfVar10 = local_14;
          pPVar11 = local_18;
        }
        else {
          pfVar7 = pfVar10 + 6;
          pPVar9 = pPVar11;
          for (; iVar8 != 0; iVar8 = iVar8 + -1) {
            *pfVar10 = (pPVar9->Vector).x;
            pPVar9 = (POINT_3D *)&(pPVar9->Vector).y;
            pfVar10 = pfVar10 + 1;
          }
          local_14 = pfVar7;
          local_18 = pPVar11;
LAB_00541096:
          local_10 = local_10 + 6;
          local_8 = local_8 + 6;
          local_c = local_c + 1;
          pfVar10 = pfVar7;
          pPVar11 = local_18;
          local_14 = pfVar7;
        }
      }
      pPVar9 = pPVar11;
      local_1c = pPVar9;
      pPVar11 = pPVar9 + 1;
      local_20 = local_20 + -1;
      local_18 = pPVar11;
    } while (local_20 != 0);
    if (local_c == 0) {
      return 0;
    }
    pPVar11 = (POINT_3D *)(pfVar10 + local_c * -6);
    local_18 = pPVar11;
    param_3 = local_c;
  }
  if ((local_24 & 4) != 0) {
    local_c = 0;
    pPVar9 = pPVar11 + param_3 + -1;
    local_1c = pPVar9;
    if (param_3 < 1) {
      return 0;
    }
    local_8 = pfVar10 + 5;
    local_10 = pfVar10 + 6;
    local_20 = param_3;
    do {
      fVar1 = (pPVar9->Vector).x;
      local_1c = pPVar9;
      if (param_1->Right <= (pPVar11->Vector).x) {
        if (fVar1 < param_1->Right) {
          ptVar4 = (tagLIGHTING *)
                   ((param_1->Right - (pPVar9->Vector).x) /
                   ((pPVar11->Vector).x - (pPVar9->Vector).x));
          *pfVar10 = param_1->Right;
          pfVar10[1] = ((pPVar11->Vector).y - (pPVar9->Vector).y) * (float)ptVar4 +
                       (pPVar9->Vector).y;
          pfVar10[2] = ((pPVar11->Vector).z - (pPVar9->Vector).z) * (float)ptVar4 +
                       (pPVar9->Vector).z;
          pfVar10[3] = ((pPVar11->Texel).u - (pPVar9->Texel).u) * (float)ptVar4 + (pPVar9->Texel).u;
          pfVar10[4] = ((pPVar11->Texel).v - (pPVar9->Texel).v) * (float)ptVar4 + (pPVar9->Texel).v;
          ClipLighting(ptVar4,unaff_EDI,unaff_ESI,unaff_EBX);
          pfVar7 = local_14 + 6;
          local_14 = pfVar7;
          goto LAB_0054121d;
        }
      }
      else {
        iVar8 = 6;
        pPVar12 = pPVar11;
        pfVar7 = local_10;
        if (param_1->Right <= fVar1) {
          for (; iVar8 != 0; iVar8 = iVar8 + -1) {
            *pfVar7 = (pPVar12->Vector).x;
            pPVar12 = (POINT_3D *)&(pPVar12->Vector).y;
            pfVar7 = pfVar7 + 1;
          }
          ptVar4 = (tagLIGHTING *)
                   ((param_1->Right - (pPVar9->Vector).x) /
                   ((pPVar11->Vector).x - (pPVar9->Vector).x));
          *pfVar10 = param_1->Right;
          pfVar10[1] = ((pPVar11->Vector).y - (pPVar9->Vector).y) * (float)ptVar4 +
                       (pPVar9->Vector).y;
          pfVar10[2] = ((pPVar11->Vector).z - (pPVar9->Vector).z) * (float)ptVar4 +
                       (pPVar9->Vector).z;
          pfVar10[3] = ((pPVar11->Texel).u - (pPVar9->Texel).u) * (float)ptVar4 + (pPVar9->Texel).u;
          pfVar10[4] = ((pPVar11->Texel).v - (pPVar9->Texel).v) * (float)ptVar4 + (pPVar9->Texel).v;
          ClipLighting(ptVar4,unaff_EDI,unaff_ESI,unaff_EBX);
          local_14 = local_14 + 0xc;
          local_10 = local_10 + 0xc;
          local_8 = local_8 + 0xc;
          local_c = local_c + 2;
          pfVar10 = local_14;
          pPVar11 = local_18;
        }
        else {
          pfVar7 = pfVar10 + 6;
          pPVar9 = pPVar11;
          for (; iVar8 != 0; iVar8 = iVar8 + -1) {
            *pfVar10 = (pPVar9->Vector).x;
            pPVar9 = (POINT_3D *)&(pPVar9->Vector).y;
            pfVar10 = pfVar10 + 1;
          }
          local_14 = pfVar7;
          local_18 = pPVar11;
LAB_0054121d:
          local_10 = local_10 + 6;
          local_8 = local_8 + 6;
          local_c = local_c + 1;
          pfVar10 = pfVar7;
          pPVar11 = local_18;
          local_14 = pfVar7;
        }
      }
      pPVar9 = pPVar11;
      local_1c = pPVar9;
      pPVar11 = pPVar9 + 1;
      local_20 = local_20 + -1;
      local_18 = pPVar11;
    } while (local_20 != 0);
    if (local_c == 0) {
      return 0;
    }
    pPVar11 = (POINT_3D *)(pfVar10 + local_c * -6);
    local_18 = pPVar11;
    param_3 = local_c;
  }
  if ((local_24 & 1) == 0) {
LAB_005413dd:
    memmove(param_2,pPVar11,param_3 * 0x18);
    if (0 < param_3) {
      pTVar5 = &param_2->Texel;
      iVar8 = param_3;
      do {
        iVar8 = iVar8 + -1;
        fVar1 = 1.0 / (((POINT_3D *)(pTVar5 + -1))->Vector).z;
        pTVar5->u = pTVar5->u * fVar1;
        pTVar5->v = fVar1 * pTVar5->v;
        pTVar5 = pTVar5 + 2;
      } while (0 < iVar8);
      return param_3;
    }
    return param_3;
  }
  local_c = 0;
  pPVar9 = pPVar11 + param_3 + -1;
  local_1c = pPVar9;
  if (0 < param_3) {
    local_8 = pfVar10 + 5;
    local_10 = pfVar10 + 6;
    local_20 = param_3;
    do {
      fVar1 = (pPVar9->Vector).y;
      local_1c = pPVar9;
      if (param_1->Top <= (pPVar11->Vector).y) {
        if (fVar1 < param_1->Top) {
          ptVar4 = (tagLIGHTING *)
                   ((param_1->Top - (pPVar9->Vector).y) / ((pPVar11->Vector).y - (pPVar9->Vector).y)
                   );
          pfVar10[1] = param_1->Top;
          *pfVar10 = ((pPVar11->Vector).x - (pPVar9->Vector).x) * (float)ptVar4 + (pPVar9->Vector).x
          ;
          pfVar10[2] = ((pPVar11->Vector).z - (pPVar9->Vector).z) * (float)ptVar4 +
                       (pPVar9->Vector).z;
          pfVar10[3] = ((pPVar11->Texel).u - (pPVar9->Texel).u) * (float)ptVar4 + (pPVar9->Texel).u;
          pfVar10[4] = ((pPVar11->Texel).v - (pPVar9->Texel).v) * (float)ptVar4 + (pPVar9->Texel).v;
          ClipLighting(ptVar4,unaff_EDI,unaff_ESI,unaff_EBX);
          pfVar7 = local_14 + 6;
          local_14 = pfVar7;
          goto LAB_005413a6;
        }
      }
      else {
        iVar8 = 6;
        pPVar12 = pPVar11;
        pfVar7 = local_10;
        if (param_1->Top <= fVar1) {
          for (; iVar8 != 0; iVar8 = iVar8 + -1) {
            *pfVar7 = (pPVar12->Vector).x;
            pPVar12 = (POINT_3D *)&(pPVar12->Vector).y;
            pfVar7 = pfVar7 + 1;
          }
          ptVar4 = (tagLIGHTING *)
                   ((param_1->Top - (pPVar9->Vector).y) / ((pPVar11->Vector).y - (pPVar9->Vector).y)
                   );
          pfVar10[1] = param_1->Top;
          *pfVar10 = ((pPVar11->Vector).x - (pPVar9->Vector).x) * (float)ptVar4 + (pPVar9->Vector).x
          ;
          pfVar10[2] = ((pPVar11->Vector).z - (pPVar9->Vector).z) * (float)ptVar4 +
                       (pPVar9->Vector).z;
          pfVar10[3] = ((pPVar11->Texel).u - (pPVar9->Texel).u) * (float)ptVar4 + (pPVar9->Texel).u;
          pfVar10[4] = ((pPVar11->Texel).v - (pPVar9->Texel).v) * (float)ptVar4 + (pPVar9->Texel).v;
          ClipLighting(ptVar4,unaff_EDI,unaff_ESI,unaff_EBX);
          local_14 = local_14 + 0xc;
          local_10 = local_10 + 0xc;
          local_8 = local_8 + 0xc;
          local_c = local_c + 2;
          pfVar10 = local_14;
          pPVar11 = local_18;
        }
        else {
          pfVar7 = pfVar10 + 6;
          pPVar9 = pPVar11;
          for (; iVar8 != 0; iVar8 = iVar8 + -1) {
            *pfVar10 = (pPVar9->Vector).x;
            pPVar9 = (POINT_3D *)&(pPVar9->Vector).y;
            pfVar10 = pfVar10 + 1;
          }
          local_14 = pfVar7;
          local_18 = pPVar11;
LAB_005413a6:
          local_10 = local_10 + 6;
          local_8 = local_8 + 6;
          local_c = local_c + 1;
          pfVar10 = pfVar7;
          pPVar11 = local_18;
          local_14 = pfVar7;
        }
      }
      pPVar9 = pPVar11;
      local_1c = pPVar9;
      pPVar11 = pPVar9 + 1;
      local_20 = local_20 + -1;
      local_18 = pPVar11;
    } while (local_20 != 0);
    if (local_c != 0) {
      pPVar11 = (POINT_3D *)(pfVar10 + local_c * -6);
      param_3 = local_c;
      local_18 = pPVar11;
      goto LAB_005413dd;
    }
  }
  return 0;
}
