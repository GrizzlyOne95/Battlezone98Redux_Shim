/*
 * Entry: 004fc5e8
 * Name: UV_Clip_Polygon
 * Namespace: Global
 * Signature: long UV_Clip_Polygon(POINT_3D * param_1, POINT_3D * param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl UV_Clip_Polygon(POINT_3D *param_1,POINT_3D *param_2,long param_3)

{
  float fVar1;
  float fVar2;
  bool bVar3;
  int in_EAX;
  POINT_3D *in_ECX;
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
  
  UV_Outcode(&local_1c,(long *)&local_18,in_ECX,in_EAX);
  if (local_1c != 0) {
    return 0;
  }
  if (local_18 != 0) {
    pfVar6 = local_cac;
    if ((local_18 & 8) != 0) {
      local_8 = 0;
      if (in_EAX < 1) {
        return 0;
      }
      local_c = local_c94;
      pPVar5 = in_ECX + in_EAX + -1;
      local_14 = in_EAX;
      do {
        pPVar8 = in_ECX;
        fVar1 = (pPVar8->Texel).u;
        fVar2 = (pPVar5->Texel).u;
        if (0.0 < fVar1 == (fVar1 == 0.0)) {
          if (0.0 < fVar2 != (fVar2 == 0.0)) {
            fVar1 = -(pPVar5->Texel).u / ((pPVar8->Texel).u - (pPVar5->Texel).u);
            *pfVar6 = ((pPVar8->Vector).x - (pPVar5->Vector).x) * fVar1 + (pPVar5->Vector).x;
            pfVar6[1] = ((pPVar8->Vector).y - (pPVar5->Vector).y) * fVar1 + (pPVar5->Vector).y;
            pfVar6[2] = ((pPVar8->Vector).z - (pPVar5->Vector).z) * fVar1 + (pPVar5->Vector).z;
            pfVar6[3] = 0.0;
            pfVar6[4] = ((pPVar8->Texel).v - (pPVar5->Texel).v) * fVar1 + (pPVar5->Texel).v;
            goto LAB_004fc728;
          }
        }
        else {
          iVar4 = 6;
          pPVar7 = pPVar8;
          pfVar10 = pfVar6;
          if (0.0 < fVar2 == (fVar2 == 0.0)) {
            fVar1 = (pPVar5->Texel).u;
            fVar2 = (pPVar8->Texel).u;
            pfVar10 = local_c;
            for (; iVar4 != 0; iVar4 = iVar4 + -1) {
              *pfVar10 = (pPVar7->Vector).x;
              pPVar7 = (POINT_3D *)&(pPVar7->Vector).y;
              pfVar10 = pfVar10 + 1;
            }
            fVar1 = -fVar1 / (fVar2 - (pPVar5->Texel).u);
            local_c = local_c + 0xc;
            *pfVar6 = ((pPVar8->Vector).x - (pPVar5->Vector).x) * fVar1 + (pPVar5->Vector).x;
            local_8 = local_8 + 2;
            pfVar6[1] = ((pPVar8->Vector).y - (pPVar5->Vector).y) * fVar1 + (pPVar5->Vector).y;
            pfVar6[2] = ((pPVar8->Vector).z - (pPVar5->Vector).z) * fVar1 + (pPVar5->Vector).z;
            pfVar6[3] = 0.0;
            pfVar6[4] = ((pPVar8->Texel).v - (pPVar5->Texel).v) * fVar1 + (pPVar5->Texel).v;
            pfVar6 = pfVar6 + 0xc;
          }
          else {
            for (; iVar4 != 0; iVar4 = iVar4 + -1) {
              *pfVar10 = (pPVar7->Vector).x;
              pPVar7 = (POINT_3D *)&(pPVar7->Vector).y;
              pfVar10 = pfVar10 + 1;
            }
LAB_004fc728:
            local_c = local_c + 6;
            local_8 = local_8 + 1;
            pfVar6 = pfVar6 + 6;
          }
        }
        local_14 = local_14 + -1;
        pPVar5 = pPVar8;
        in_ECX = pPVar8 + 1;
      } while (local_14 != 0);
      if (local_8 == 0) {
        return 0;
      }
      in_ECX = (POINT_3D *)(pfVar6 + local_8 * -6);
      local_14 = 0;
      in_EAX = local_8;
      local_10 = pPVar8;
    }
    if ((local_18 & 2) != 0) {
      local_8 = 0;
      local_10 = in_ECX + in_EAX + -1;
      if (in_EAX < 1) {
        return 0;
      }
      local_c = pfVar6 + 6;
      local_14 = in_EAX;
      pPVar5 = in_ECX + in_EAX + -1;
      do {
        fVar1 = (in_ECX->Texel).v;
        fVar2 = (pPVar5->Texel).v;
        if (0.0 < fVar1 == (fVar1 == 0.0)) {
          if (0.0 < fVar2 != (fVar2 == 0.0)) {
            fVar1 = -(pPVar5->Texel).v / ((in_ECX->Texel).v - (pPVar5->Texel).v);
            *pfVar6 = ((in_ECX->Vector).x - (pPVar5->Vector).x) * fVar1 + (pPVar5->Vector).x;
            pfVar6[1] = ((in_ECX->Vector).y - (pPVar5->Vector).y) * fVar1 + (pPVar5->Vector).y;
            pfVar6[2] = ((in_ECX->Vector).z - (pPVar5->Vector).z) * fVar1 + (pPVar5->Vector).z;
            pfVar6[3] = ((in_ECX->Texel).u - (pPVar5->Texel).u) * fVar1 + (pPVar5->Texel).u;
            pfVar6[4] = 0.0;
            goto LAB_004fc849;
          }
        }
        else {
          iVar4 = 6;
          pPVar8 = in_ECX;
          pfVar10 = local_c;
          pfVar9 = pfVar6;
          if (0.0 < fVar2 == (fVar2 == 0.0)) {
            for (; iVar4 != 0; iVar4 = iVar4 + -1) {
              *pfVar10 = (pPVar8->Vector).x;
              pPVar8 = (POINT_3D *)&(pPVar8->Vector).y;
              pfVar10 = pfVar10 + 1;
            }
            fVar1 = -(pPVar5->Texel).v / ((in_ECX->Texel).v - (pPVar5->Texel).v);
            local_c = local_c + 0xc;
            *pfVar6 = ((in_ECX->Vector).x - (pPVar5->Vector).x) * fVar1 + (pPVar5->Vector).x;
            local_8 = local_8 + 2;
            pfVar6[1] = ((in_ECX->Vector).y - (pPVar5->Vector).y) * fVar1 + (pPVar5->Vector).y;
            pfVar6[2] = ((in_ECX->Vector).z - (pPVar5->Vector).z) * fVar1 + (pPVar5->Vector).z;
            pfVar6[3] = ((in_ECX->Texel).u - (pPVar5->Texel).u) * fVar1 + (pPVar5->Texel).u;
            pfVar6[4] = 0.0;
            pfVar6 = pfVar6 + 0xc;
          }
          else {
            for (; iVar4 != 0; iVar4 = iVar4 + -1) {
              *pfVar9 = (pPVar8->Vector).x;
              pPVar8 = (POINT_3D *)&(pPVar8->Vector).y;
              pfVar9 = pfVar9 + 1;
            }
LAB_004fc849:
            local_c = local_c + 6;
            local_8 = local_8 + 1;
            pfVar6 = pfVar6 + 6;
          }
        }
        local_10 = in_ECX;
        local_14 = local_14 + -1;
        pPVar5 = in_ECX;
        in_ECX = in_ECX + 1;
      } while (local_14 != 0);
      if (local_8 == 0) {
        return 0;
      }
      in_ECX = (POINT_3D *)(pfVar6 + local_8 * -6);
      in_EAX = local_8;
    }
    if ((local_18 & 4) != 0) {
      local_8 = 0;
      local_10 = in_ECX + in_EAX + -1;
      if (in_EAX < 1) {
        return 0;
      }
      local_c = pfVar6 + 6;
      local_14 = in_EAX;
      pPVar5 = in_ECX + in_EAX + -1;
      do {
        bVar3 = 1.0 < (pPVar5->Texel).u;
        if (1.0 < (in_ECX->Texel).u) {
          if (!bVar3) {
            fVar1 = (1.0 - (pPVar5->Texel).u) / ((in_ECX->Texel).u - (pPVar5->Texel).u);
            *pfVar6 = ((in_ECX->Vector).x - (pPVar5->Vector).x) * fVar1 + (pPVar5->Vector).x;
            pfVar6[1] = ((in_ECX->Vector).y - (pPVar5->Vector).y) * fVar1 + (pPVar5->Vector).y;
            pfVar6[2] = ((in_ECX->Vector).z - (pPVar5->Vector).z) * fVar1 + (pPVar5->Vector).z;
            pfVar6[3] = 1.0;
            pfVar6[4] = ((in_ECX->Texel).v - (pPVar5->Texel).v) * fVar1 + (pPVar5->Texel).v;
            goto LAB_004fc97a;
          }
        }
        else {
          iVar4 = 6;
          pPVar8 = in_ECX;
          pfVar10 = local_c;
          pfVar9 = pfVar6;
          if (bVar3) {
            for (; iVar4 != 0; iVar4 = iVar4 + -1) {
              *pfVar10 = (pPVar8->Vector).x;
              pPVar8 = (POINT_3D *)&(pPVar8->Vector).y;
              pfVar10 = pfVar10 + 1;
            }
            fVar1 = (1.0 - (pPVar5->Texel).u) / ((in_ECX->Texel).u - (pPVar5->Texel).u);
            local_c = local_c + 0xc;
            *pfVar6 = ((in_ECX->Vector).x - (pPVar5->Vector).x) * fVar1 + (pPVar5->Vector).x;
            local_8 = local_8 + 2;
            pfVar6[1] = ((in_ECX->Vector).y - (pPVar5->Vector).y) * fVar1 + (pPVar5->Vector).y;
            pfVar6[2] = ((in_ECX->Vector).z - (pPVar5->Vector).z) * fVar1 + (pPVar5->Vector).z;
            pfVar6[3] = 1.0;
            pfVar6[4] = ((in_ECX->Texel).v - (pPVar5->Texel).v) * fVar1 + (pPVar5->Texel).v;
            pfVar6 = pfVar6 + 0xc;
          }
          else {
            for (; iVar4 != 0; iVar4 = iVar4 + -1) {
              *pfVar9 = (pPVar8->Vector).x;
              pPVar8 = (POINT_3D *)&(pPVar8->Vector).y;
              pfVar9 = pfVar9 + 1;
            }
LAB_004fc97a:
            local_c = local_c + 6;
            local_8 = local_8 + 1;
            pfVar6 = pfVar6 + 6;
          }
        }
        local_10 = in_ECX;
        local_14 = local_14 + -1;
        pPVar5 = in_ECX;
        in_ECX = in_ECX + 1;
      } while (local_14 != 0);
      if (local_8 == 0) {
        return 0;
      }
      in_ECX = (POINT_3D *)(pfVar6 + local_8 * -6);
      in_EAX = local_8;
    }
    if ((local_18 & 1) != 0) {
      local_8 = 0;
      local_10 = in_ECX + in_EAX + -1;
      if (0 < in_EAX) {
        local_c = pfVar6 + 6;
        local_14 = in_EAX;
        pPVar5 = in_ECX + in_EAX + -1;
        do {
          fVar1 = (pPVar5->Texel).v;
          if (1.0 <= (in_ECX->Texel).v) {
            if (fVar1 < 1.0) {
              fVar1 = (1.0 - (pPVar5->Texel).v) / ((in_ECX->Texel).v - (pPVar5->Texel).v);
              *pfVar6 = ((in_ECX->Vector).x - (pPVar5->Vector).x) * fVar1 + (pPVar5->Vector).x;
              pfVar6[1] = ((in_ECX->Vector).y - (pPVar5->Vector).y) * fVar1 + (pPVar5->Vector).y;
              pfVar6[2] = ((in_ECX->Vector).z - (pPVar5->Vector).z) * fVar1 + (pPVar5->Vector).z;
              pfVar6[3] = ((in_ECX->Texel).u - (pPVar5->Texel).u) * fVar1 + (pPVar5->Texel).u;
              pfVar6[4] = 1.0;
              goto LAB_004fca9b;
            }
          }
          else {
            iVar4 = 6;
            pPVar8 = in_ECX;
            pfVar10 = local_c;
            pfVar9 = pfVar6;
            if (1.0 <= fVar1) {
              for (; iVar4 != 0; iVar4 = iVar4 + -1) {
                *pfVar10 = (pPVar8->Vector).x;
                pPVar8 = (POINT_3D *)&(pPVar8->Vector).y;
                pfVar10 = pfVar10 + 1;
              }
              fVar1 = (1.0 - (pPVar5->Texel).v) / ((in_ECX->Texel).v - (pPVar5->Texel).v);
              local_c = local_c + 0xc;
              *pfVar6 = ((in_ECX->Vector).x - (pPVar5->Vector).x) * fVar1 + (pPVar5->Vector).x;
              local_8 = local_8 + 2;
              pfVar6[1] = ((in_ECX->Vector).y - (pPVar5->Vector).y) * fVar1 + (pPVar5->Vector).y;
              pfVar6[2] = ((in_ECX->Vector).z - (pPVar5->Vector).z) * fVar1 + (pPVar5->Vector).z;
              pfVar6[3] = ((in_ECX->Texel).u - (pPVar5->Texel).u) * fVar1 + (pPVar5->Texel).u;
              pfVar6[4] = 1.0;
              pfVar6 = pfVar6 + 0xc;
            }
            else {
              for (; iVar4 != 0; iVar4 = iVar4 + -1) {
                *pfVar9 = (pPVar8->Vector).x;
                pPVar8 = (POINT_3D *)&(pPVar8->Vector).y;
                pfVar9 = pfVar9 + 1;
              }
LAB_004fca9b:
              local_c = local_c + 6;
              local_8 = local_8 + 1;
              pfVar6 = pfVar6 + 6;
            }
          }
          local_10 = in_ECX;
          local_14 = local_14 + -1;
          pPVar5 = in_ECX;
          in_ECX = in_ECX + 1;
        } while (local_14 != 0);
        if (local_8 != 0) {
          in_ECX = (POINT_3D *)(pfVar6 + local_8 * -6);
          in_EAX = local_8;
          goto LAB_004fcad0;
        }
      }
      return 0;
    }
  }
LAB_004fcad0:
  memmove(param_1,in_ECX,in_EAX * 0x18);
  return in_EAX;
}
