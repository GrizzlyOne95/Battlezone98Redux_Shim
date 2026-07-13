/*
 * Entry: 0040fb50
 * Name: FindChange
 * Namespace: Global
 * Signature: bool FindChange(VECTOR_2D * param_1, VECTOR_2D * param_2, _func___cdecl_int_long_long * param_3, float * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl
FindChange(VECTOR_2D *param_1,VECTOR_2D *param_2,_func___cdecl_int_long_long *param_3,float *param_4
          )

{
  VECTOR_2D VVar1;
  VECTOR_2D VVar2;
  VECTOR_2D VVar3;
  VECTOR_2D VVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float *in_EAX;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  int iVar9;
  float *in_ECX;
  int iVar10;
  int iVar11;
  float *unaff_ESI;
  int iVar12;
  float unaff_EDI;
  int iVar13;
  int local_30;
  int local_2c;
  int local_28;
  uint local_24;
  float local_20;
  float local_1c;
  uint local_18;
  float local_14;
  float local_10;
  float local_c;
  int local_8;
  
  fVar5 = *in_ECX * Terrain.Grid_Scale;
  fVar6 = in_ECX[1] * Terrain.Grid_Scale;
  fVar7 = *in_EAX * Terrain.Grid_Scale;
  fVar8 = Terrain.Grid_Scale * in_EAX[1];
  floor((double)fVar5);
  _ftol2_sse();
  floor((double)(param_2->x * fVar7 + fVar5));
  _ftol2_sse();
  floor((double)fVar6);
  _ftol2_sse();
  floor((double)(param_2->x * fVar8 + fVar6));
  _ftol2_sse();
  local_20 = (fVar5 - 0.5) - (float)extraout_EAX;
  local_28 = 1;
  local_2c = 1;
  local_1c = (fVar6 - 0.5) - (float)extraout_EAX_01;
  local_18 = TerrainOutCode(extraout_EAX,extraout_EAX_01);
  local_24 = TerrainOutCode(extraout_EAX_00,extraout_EAX_02);
  iVar11 = extraout_EAX_02;
  iVar12 = extraout_EAX_01;
  iVar13 = extraout_EAX;
  local_30 = extraout_EAX_02;
  local_8 = extraout_EAX_00;
  while (local_24 != 0 || local_18 != 0) {
    if ((local_18 & local_24) != 0) {
      return false;
    }
    local_c = (float)local_18;
    if (local_18 == 0) {
      local_c = (float)local_24;
    }
    if (((uint)local_c & 8) == 0) {
      if (((uint)local_c & 4) == 0) {
        if (((uint)local_c & 2) == 0) {
          iVar9 = ((GridMaxZ - iVar12) * (local_8 - iVar13)) / (iVar11 - iVar12);
          iVar10 = GridMaxZ;
          iVar11 = local_30;
        }
        else {
          iVar9 = ((GridMinZ - iVar12) * (local_8 - iVar13)) / (iVar11 - iVar12);
          iVar10 = GridMinZ;
        }
        iVar9 = iVar9 + iVar13;
      }
      else {
        iVar10 = ((GridMaxX - iVar13) * (iVar11 - iVar12)) / (local_8 - iVar13) + iVar12;
        iVar9 = GridMaxX;
      }
    }
    else {
      iVar10 = ((GridMinX - iVar13) * (iVar11 - iVar12)) / (local_8 - iVar13) + iVar12;
      iVar9 = GridMinX;
    }
    if (local_c == (float)local_18) {
      local_18 = TerrainOutCode(iVar9,iVar10);
      iVar12 = iVar10;
      iVar13 = iVar9;
    }
    else {
      local_24 = TerrainOutCode(iVar9,iVar10);
      iVar11 = iVar10;
      local_30 = iVar10;
      local_8 = iVar9;
    }
  }
  local_8 = local_8 - iVar13;
  iVar11 = iVar11 - iVar12;
  local_14 = fVar7;
  if (fVar7 < 0.0) {
    local_8 = -local_8;
    local_28 = -1;
    local_20 = -local_20;
    local_14 = -fVar7;
  }
  local_10 = fVar8;
  if (fVar8 < 0.0) {
    iVar11 = -iVar11;
    local_2c = -1;
    local_1c = -local_1c;
    local_10 = -fVar8;
  }
  if (local_14 <= local_10) {
    local_c = (0.5 - local_1c) * local_14 - (0.5 - local_20) * local_10;
    while (-1 < iVar11) {
      iVar11 = iVar11 + -1;
      iVar9 = (*(code *)param_1)(iVar13,iVar12);
      if (iVar9 != 0) goto LAB_0040fdf8;
      if (0.0 < local_c) {
        iVar13 = iVar13 + local_28;
        local_c = local_c - local_10;
        iVar9 = (*(code *)param_1)(iVar13,iVar12);
        if (iVar9 != 0) goto LAB_0040fddc;
      }
      iVar12 = iVar12 + local_2c;
      local_c = local_c + local_14;
    }
  }
  else {
    local_c = (0.5 - local_20) * local_10 - (0.5 - local_1c) * local_14;
    while (-1 < local_8) {
      local_8 = local_8 + -1;
      iVar11 = (*(code *)param_1)(iVar13,iVar12);
      if (iVar11 != 0) {
LAB_0040fddc:
        VVar1.z = fVar7;
        VVar1.x = fVar6;
        VVar3.z = unaff_EDI;
        VVar3.x = fVar8;
        ChangeIntersectionH(iVar13,(int)fVar5,VVar1,VVar3,unaff_ESI);
        return true;
      }
      if (0.0 < local_c) {
        iVar12 = iVar12 + local_2c;
        local_c = local_c - local_14;
        iVar11 = (*(code *)param_1)(iVar13,iVar12);
        if (iVar11 != 0) {
LAB_0040fdf8:
          VVar2.z = fVar7;
          VVar2.x = fVar6;
          VVar4.z = unaff_EDI;
          VVar4.x = fVar8;
          ChangeIntersectionV(iVar12,(int)fVar5,VVar2,VVar4,unaff_ESI);
          return true;
        }
      }
      iVar13 = iVar13 + local_28;
      local_c = local_c + local_10;
    }
  }
  return false;
}
