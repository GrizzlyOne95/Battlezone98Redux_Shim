/*
 * Entry: 0054270f
 * Name: D3D_Clip_3D_UV_Polygon
 * Namespace: Global
 * Signature: long D3D_Clip_3D_UV_Polygon(CAMERA * param_1, POINT_3D * param_2, POINT_3D * param_3, long param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl
D3D_Clip_3D_UV_Polygon
          (CAMERA *param_1,POINT_3D *param_2,POINT_3D *param_3,long param_4,long param_5)

{
  float fVar1;
  float fVar2;
  tagLIGHTING *ptVar3;
  long lVar4;
  int iVar5;
  POINT_3D *pPVar6;
  float *pfVar7;
  float unaff_EBX;
  tagLIGHTING *unaff_ESI;
  POINT_3D *pPVar8;
  tagLIGHTING *unaff_EDI;
  float *pfVar9;
  float local_68c [5];
  float local_678;
  float local_674 [402];
  int local_2c;
  float local_28;
  float local_24;
  uint local_20;
  int local_1c;
  POINT_3D *local_18;
  float *local_14;
  int local_10;
  float *local_c;
  float *local_8;
  
  local_28 = param_1->View_Frustrum[0].z;
  local_24 = param_1->View_Frustrum[4].z;
  Compute_Outcode_Z(&local_2c,(long *)&local_20,param_3,param_4,local_28,local_24);
  if (local_2c != 0) {
    return 0;
  }
  if (local_20 == 0) {
LAB_00542a9d:
    D3D_Clip_3D_UV_Project_Only(param_1,param_2,param_3,param_4,param_5);
    lVar4 = D3D_Clip_2D_UV(param_1,param_2,param_4,param_5);
  }
  else {
    pfVar7 = local_68c;
    local_14 = pfVar7;
    pPVar6 = param_3;
    if ((local_20 & 2) == 0) {
LAB_00542815:
      param_3 = pPVar6;
      if (((local_20 & 1) == 0) || ((D3IniFlags & 0x200000U) != 0)) goto LAB_00542a9d;
      local_10 = 0;
      local_18 = param_3 + param_4 + -1;
      if (0 < param_4) {
        local_8 = pfVar7 + 5;
        local_c = pfVar7 + 6;
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
              pfVar7[2] = local_24;
              *pfVar7 = ((param_3->Vector).x - (pPVar6->Vector).x) * (float)ptVar3 +
                        (pPVar6->Vector).x;
              pfVar7[1] = ((param_3->Vector).y - (pPVar6->Vector).y) * (float)ptVar3 +
                          (pPVar6->Vector).y;
              pfVar7[3] = ((param_3->Texel).u - (pPVar6->Texel).u) * (float)ptVar3 +
                          (pPVar6->Texel).u;
              pfVar7[4] = ((param_3->Texel).v - (pPVar6->Texel).v) * (float)ptVar3 +
                          (pPVar6->Texel).v;
              ClipLighting(ptVar3,unaff_EDI,unaff_ESI,unaff_EBX);
              local_14 = local_14 + 6;
              local_c = local_c + 6;
              local_8 = local_8 + 6;
              local_10 = local_10 + 1;
              pfVar7 = local_14;
            }
          }
          else {
            iVar5 = 6;
            pPVar8 = param_3;
            pfVar9 = local_c;
            if (fVar1 < local_24) {
              local_c = local_c + 6;
              local_8 = local_8 + 6;
              local_10 = local_10 + 1;
              pPVar6 = param_3;
              pfVar9 = pfVar7;
              for (; iVar5 != 0; iVar5 = iVar5 + -1) {
                *pfVar9 = (pPVar6->Vector).x;
                pPVar6 = (POINT_3D *)&(pPVar6->Vector).y;
                pfVar9 = pfVar9 + 1;
              }
              local_14 = pfVar7 + 6;
              pfVar7 = pfVar7 + 6;
            }
            else {
              for (; iVar5 != 0; iVar5 = iVar5 + -1) {
                *pfVar9 = (pPVar8->Vector).x;
                pPVar8 = (POINT_3D *)&(pPVar8->Vector).y;
                pfVar9 = pfVar9 + 1;
              }
              ptVar3 = (tagLIGHTING *)
                       ((local_24 - (pPVar6->Vector).z) / ((param_3->Vector).z - (pPVar6->Vector).z)
                       );
              pfVar7[2] = local_24;
              *pfVar7 = ((param_3->Vector).x - (pPVar6->Vector).x) * (float)ptVar3 +
                        (pPVar6->Vector).x;
              pfVar7[1] = ((param_3->Vector).y - (pPVar6->Vector).y) * (float)ptVar3 +
                          (pPVar6->Vector).y;
              pfVar7[3] = ((param_3->Texel).u - (pPVar6->Texel).u) * (float)ptVar3 +
                          (pPVar6->Texel).u;
              pfVar7[4] = ((param_3->Texel).v - (pPVar6->Texel).v) * (float)ptVar3 +
                          (pPVar6->Texel).v;
              ClipLighting(ptVar3,unaff_EDI,unaff_ESI,unaff_EBX);
              local_14 = local_14 + 0xc;
              local_c = local_c + 0xc;
              local_8 = local_8 + 0xc;
              local_10 = local_10 + 2;
              pfVar7 = local_14;
            }
          }
          local_18 = param_3;
          local_1c = local_1c + -1;
          pPVar6 = param_3;
          param_3 = param_3 + 1;
        } while (local_1c != 0);
        if (local_10 != 0) {
          param_3 = (POINT_3D *)(pfVar7 + local_10 * -6);
          param_4 = local_10;
          goto LAB_00542a9d;
        }
      }
    }
    else {
      local_10 = 0;
      if (0 < param_4) {
        local_8 = &local_678;
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
              pfVar7[2] = local_28;
              *pfVar7 = ((param_3->Vector).x - (pPVar6->Vector).x) * (float)ptVar3 +
                        (pPVar6->Vector).x;
              pfVar7[1] = ((param_3->Vector).y - (pPVar6->Vector).y) * (float)ptVar3 +
                          (pPVar6->Vector).y;
              pfVar7[3] = ((param_3->Texel).u - (pPVar6->Texel).u) * (float)ptVar3 +
                          (pPVar6->Texel).u;
              pfVar7[4] = ((param_3->Texel).v - (pPVar6->Texel).v) * (float)ptVar3 +
                          (pPVar6->Texel).v;
              ClipLighting(ptVar3,unaff_EDI,unaff_ESI,unaff_EBX);
              local_14 = local_14 + 6;
              local_c = local_c + 6;
              local_8 = local_8 + 6;
              local_10 = local_10 + 1;
              pfVar7 = local_14;
            }
          }
          else {
            iVar5 = 6;
            if (local_28 < fVar2 == (local_28 == fVar2)) {
              fVar1 = (pPVar6->Vector).z;
              fVar2 = (param_3->Vector).z;
              pPVar8 = param_3;
              pfVar9 = local_c;
              for (; iVar5 != 0; iVar5 = iVar5 + -1) {
                *pfVar9 = (pPVar8->Vector).x;
                pPVar8 = (POINT_3D *)&(pPVar8->Vector).y;
                pfVar9 = pfVar9 + 1;
              }
              ptVar3 = (tagLIGHTING *)((local_28 - fVar1) / (fVar2 - (pPVar6->Vector).z));
              pfVar7[2] = local_28;
              *pfVar7 = ((param_3->Vector).x - (pPVar6->Vector).x) * (float)ptVar3 +
                        (pPVar6->Vector).x;
              pfVar7[1] = ((param_3->Vector).y - (pPVar6->Vector).y) * (float)ptVar3 +
                          (pPVar6->Vector).y;
              pfVar7[3] = ((param_3->Texel).u - (pPVar6->Texel).u) * (float)ptVar3 +
                          (pPVar6->Texel).u;
              pfVar7[4] = ((param_3->Texel).v - (pPVar6->Texel).v) * (float)ptVar3 +
                          (pPVar6->Texel).v;
              ClipLighting(ptVar3,unaff_EDI,unaff_ESI,unaff_EBX);
              local_14 = local_14 + 0xc;
              local_c = local_c + 0xc;
              local_8 = local_8 + 0xc;
              local_10 = local_10 + 2;
              pfVar7 = local_14;
            }
            else {
              local_c = local_c + 6;
              local_8 = local_8 + 6;
              local_10 = local_10 + 1;
              pPVar6 = param_3;
              pfVar9 = pfVar7;
              for (; iVar5 != 0; iVar5 = iVar5 + -1) {
                *pfVar9 = (pPVar6->Vector).x;
                pPVar6 = (POINT_3D *)&(pPVar6->Vector).y;
                pfVar9 = pfVar9 + 1;
              }
              local_14 = pfVar7 + 6;
              pfVar7 = pfVar7 + 6;
            }
          }
          local_1c = local_1c + -1;
          pPVar6 = param_3;
          pPVar8 = param_3 + 1;
        } while (local_1c != 0);
        if (local_10 != 0) {
          local_1c = 0;
          param_4 = local_10;
          pPVar6 = (POINT_3D *)(pfVar7 + local_10 * -6);
          local_18 = param_3;
          goto LAB_00542815;
        }
      }
    }
    lVar4 = 0;
  }
  return lVar4;
}
