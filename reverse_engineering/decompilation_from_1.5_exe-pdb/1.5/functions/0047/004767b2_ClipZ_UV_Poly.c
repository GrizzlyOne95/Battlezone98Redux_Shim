/*
 * Entry: 004767b2
 * Name: ClipZ_UV_Poly
 * Namespace: Global
 * Signature: long ClipZ_UV_Poly(float param_1, float param_2, POINT_3D * param_3, POINT_3D * param_4, long param_5, tagLIGHTING param_6, tagLIGHTING param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl
ClipZ_UV_Poly(float param_1,float param_2,POINT_3D *param_3,POINT_3D *param_4,long param_5,
             tagLIGHTING param_6,tagLIGHTING param_7)

{
  float fVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  POINT_3D *pPVar8;
  float *pfVar9;
  float *pfVar10;
  POINT_3D *pPVar11;
  long lVar12;
  POINT_3D *pPVar13;
  float local_674 [6];
  POINT_3D local_65c [67];
  uint local_14;
  POINT_3D **local_10;
  POINT_3D **local_c;
  POINT_3D *local_8;
  
  local_c = &local_8;
  local_10 = (POINT_3D **)&local_14;
  uVar5 = 0xff;
  local_14 = 0;
  pPVar8 = param_4;
  lVar12 = param_5;
  do {
    fVar1 = (pPVar8->Vector).z;
    pPVar8 = pPVar8 + 1;
    uVar7 = (uint)(fVar1 < param_1) * 2 + (uint)(fVar1 < param_2) ^ 1;
    uVar5 = uVar5 & uVar7;
    local_14 = local_14 | uVar7;
    lVar12 = lVar12 + -1;
  } while (lVar12 != 0);
  if (uVar5 != 0) {
    return 0;
  }
  if (local_14 == 0) {
    memcpy(param_3,param_4,param_5 * 0x18);
    return param_5;
  }
  if ((local_14 & 2) != 0) {
    local_c = (POINT_3D **)0x0;
    if (param_5 < 1) {
      return 0;
    }
    local_8 = local_65c;
    local_10 = (POINT_3D **)param_5;
    pPVar8 = param_4 + param_5 + -1;
    pfVar9 = local_674;
    do {
      fVar1 = (param_4->Vector).z;
      fVar2 = (pPVar8->Vector).z;
      if (param_1 < fVar1 == (param_1 == fVar1)) {
        pfVar10 = pfVar9;
        if (param_1 < fVar2 != (param_1 == fVar2)) {
          local_8 = local_8 + 1;
          fVar1 = (param_1 - (pPVar8->Vector).z) / ((param_4->Vector).z - (pPVar8->Vector).z);
          pfVar9[2] = param_1;
          *pfVar9 = ((param_4->Vector).x - (pPVar8->Vector).x) * fVar1 + (pPVar8->Vector).x;
          pfVar10 = pfVar9 + 6;
          local_c = (POINT_3D **)((int)local_c + 1);
          pfVar9[1] = ((param_4->Vector).y - (pPVar8->Vector).y) * fVar1 + (pPVar8->Vector).y;
          pfVar9[3] = ((param_4->Texel).u - (pPVar8->Texel).u) * fVar1 + (pPVar8->Texel).u;
          pfVar9[4] = ((param_4->Texel).v - (pPVar8->Texel).v) * fVar1 + (pPVar8->Texel).v;
          *(tagLIGHTING *)(pfVar9 + 5) = param_6;
        }
      }
      else {
        iVar6 = 6;
        if (param_1 < fVar2 == (param_1 == fVar2)) {
          fVar1 = (pPVar8->Vector).z;
          fVar2 = (param_4->Vector).z;
          fVar3 = (pPVar8->Vector).z;
          pPVar11 = param_4;
          pPVar13 = local_8;
          for (; iVar6 != 0; iVar6 = iVar6 + -1) {
            (pPVar13->Vector).x = (pPVar11->Vector).x;
            pPVar11 = (POINT_3D *)&(pPVar11->Vector).y;
            pPVar13 = (POINT_3D *)&(pPVar13->Vector).y;
          }
          fVar1 = (param_1 - fVar1) / (fVar2 - fVar3);
          local_8 = local_8 + 2;
          pfVar9[2] = param_1;
          *pfVar9 = ((param_4->Vector).x - (pPVar8->Vector).x) * fVar1 + (pPVar8->Vector).x;
          pfVar10 = pfVar9 + 0xc;
          local_c = (POINT_3D **)((int)local_c + 2);
          pfVar9[1] = ((param_4->Vector).y - (pPVar8->Vector).y) * fVar1 + (pPVar8->Vector).y;
          pfVar9[3] = ((param_4->Texel).u - (pPVar8->Texel).u) * fVar1 + (pPVar8->Texel).u;
          pfVar9[4] = ((param_4->Texel).v - (pPVar8->Texel).v) * fVar1 + (pPVar8->Texel).v;
          *(tagLIGHTING *)(pfVar9 + 5) = param_6;
        }
        else {
          local_8 = local_8 + 1;
          pPVar8 = param_4;
          pfVar10 = pfVar9;
          for (; iVar6 != 0; iVar6 = iVar6 + -1) {
            *pfVar10 = (pPVar8->Vector).x;
            pPVar8 = (POINT_3D *)&(pPVar8->Vector).y;
            pfVar10 = pfVar10 + 1;
          }
          local_c = (POINT_3D **)((int)local_c + 1);
          pfVar10 = pfVar9 + 6;
        }
      }
      local_10 = (POINT_3D **)((int)local_10 + -1);
      pPVar8 = param_4;
      pfVar9 = pfVar10;
      param_4 = param_4 + 1;
    } while (local_10 != (POINT_3D **)0x0);
    if (local_c == (POINT_3D **)0x0) {
      return 0;
    }
    param_4 = (POINT_3D *)(pfVar10 + (int)local_c * -6);
    param_5 = (long)local_c;
  }
  if ((local_14 & 1) == 0) {
    return (long)local_c;
  }
  local_c = (POINT_3D **)0x0;
  if (0 < param_5) {
    local_8 = param_3 + 1;
    local_10 = (POINT_3D **)param_5;
    pPVar8 = param_4 + param_5 + -1;
    do {
      bVar4 = param_2 < (pPVar8->Vector).z;
      if (param_2 < (param_4->Vector).z) {
        pPVar11 = param_3;
        if (!bVar4) {
          local_8 = local_8 + 1;
          fVar1 = (param_2 - (pPVar8->Vector).z) / ((param_4->Vector).z - (pPVar8->Vector).z);
          (param_3->Vector).z = param_2;
          (param_3->Vector).x =
               ((param_4->Vector).x - (pPVar8->Vector).x) * fVar1 + (pPVar8->Vector).x;
          pPVar11 = param_3 + 1;
          local_c = (POINT_3D **)((int)local_c + 1);
          (param_3->Vector).y =
               ((param_4->Vector).y - (pPVar8->Vector).y) * fVar1 + (pPVar8->Vector).y;
          (param_3->Texel).u = ((param_4->Texel).u - (pPVar8->Texel).u) * fVar1 + (pPVar8->Texel).u;
          (param_3->Texel).v = ((param_4->Texel).v - (pPVar8->Texel).v) * fVar1 + (pPVar8->Texel).v;
          (param_3->Texel).field2_0x8 = (TEXEL_u_8)param_7;
        }
      }
      else {
        iVar6 = 6;
        pPVar11 = param_4;
        pPVar13 = local_8;
        if (bVar4) {
          for (; iVar6 != 0; iVar6 = iVar6 + -1) {
            (pPVar13->Vector).x = (pPVar11->Vector).x;
            pPVar11 = (POINT_3D *)&(pPVar11->Vector).y;
            pPVar13 = (POINT_3D *)&(pPVar13->Vector).y;
          }
          param_3[1].Texel.field2_0x8 = (TEXEL_u_8)param_6;
          fVar1 = (param_2 - (pPVar8->Vector).z) / ((param_4->Vector).z - (pPVar8->Vector).z);
          local_8 = local_8 + 2;
          (param_3->Vector).z = param_2;
          (param_3->Vector).x =
               ((param_4->Vector).x - (pPVar8->Vector).x) * fVar1 + (pPVar8->Vector).x;
          pPVar11 = param_3 + 2;
          local_c = (POINT_3D **)((int)local_c + 2);
          (param_3->Vector).y =
               ((param_4->Vector).y - (pPVar8->Vector).y) * fVar1 + (pPVar8->Vector).y;
          (param_3->Texel).u = ((param_4->Texel).u - (pPVar8->Texel).u) * fVar1 + (pPVar8->Texel).u;
          (param_3->Texel).v = ((param_4->Texel).v - (pPVar8->Texel).v) * fVar1 + (pPVar8->Texel).v;
          (param_3->Texel).field2_0x8 = (TEXEL_u_8)param_7;
        }
        else {
          local_8 = local_8 + 1;
          pPVar8 = param_4;
          pPVar11 = param_3;
          for (; iVar6 != 0; iVar6 = iVar6 + -1) {
            (pPVar11->Vector).x = (pPVar8->Vector).x;
            pPVar8 = (POINT_3D *)&(pPVar8->Vector).y;
            pPVar11 = (POINT_3D *)&(pPVar11->Vector).y;
          }
          (param_3->Texel).field2_0x8 = (TEXEL_u_8)param_6;
          pPVar11 = param_3 + 1;
          local_c = (POINT_3D **)((int)local_c + 1);
        }
      }
      local_10 = (POINT_3D **)((int)local_10 + -1);
      pPVar8 = param_4;
      param_3 = pPVar11;
      param_4 = param_4 + 1;
    } while (local_10 != (POINT_3D **)0x0);
    if (local_c != (POINT_3D **)0x0) {
      return (long)local_c;
    }
  }
  return 0;
}
