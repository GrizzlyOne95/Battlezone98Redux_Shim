/*
 * Entry: 0051e5a6
 * Name: Terrain_FindChange
 * Namespace: Global
 * Signature: int Terrain_FindChange(VECTOR_3D_LONG param_1, VECTOR_3D param_2, _func___cdecl_int_long_long * param_3, float * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
Terrain_FindChange(VECTOR_3D_LONG param_1,VECTOR_3D param_2,_func___cdecl_int_long_long *param_3,
                  float *param_4)

{
  double dVar1;
  double dVar2;
  VECTOR_3D_LONG VVar3;
  VECTOR_3D_LONG VVar4;
  VECTOR_3D VVar5;
  VECTOR_3D VVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  int iVar13;
  int iVar14;
  float *unaff_ESI;
  int iVar15;
  float unaff_EDI;
  int iVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  int local_44;
  int local_34;
  int local_30;
  long local_2c;
  uint local_28;
  float local_24;
  float local_20;
  uint local_1c;
  long local_18;
  float local_14;
  float local_10;
  float local_c;
  long local_8;
  
  fVar7 = (float)param_1.x * Terrain.Grid_Scale;
  dVar1 = (double)fVar7;
  fVar8 = (float)param_1.y * Terrain.Grid_Scale;
  fVar9 = (float)param_1.z * Terrain.Grid_Scale;
  dVar2 = (double)fVar9;
  fVar10 = param_2.x * Terrain.Grid_Scale;
  fVar11 = param_2.y * Terrain.Grid_Scale;
  fVar12 = Terrain.Grid_Scale * param_2.z;
  Set_Rounding((int)unaff_EDI);
  local_44 = (int)(longlong)ROUND(dVar1);
  iVar15 = local_44;
  local_18 = local_44;
  local_44 = (int)(longlong)ROUND(*param_4 * fVar10 + fVar7);
  iVar16 = local_44;
  local_8 = local_44;
  local_44 = (int)(longlong)ROUND(dVar2);
  iVar14 = local_44;
  local_44 = (int)(longlong)ROUND(*param_4 * fVar12 + fVar9);
  local_2c = local_44;
  Set_Rounding((int)unaff_EDI);
  local_30 = 1;
  local_24 = (fVar7 - 0.5) - (float)iVar15;
  local_20 = (fVar9 - 0.5) - (float)iVar14;
  local_34 = 1;
  local_1c = TerrainOutCode(iVar15,iVar14);
  local_28 = TerrainOutCode(iVar16,local_44);
  while (local_28 != 0 || local_1c != 0) {
    if ((local_1c & local_28) != 0) {
      return 0;
    }
    local_c = (float)local_1c;
    if (local_1c == 0) {
      local_c = (float)local_28;
    }
    if (((uint)local_c & 8) == 0) {
      if (((uint)local_c & 4) == 0) {
        if (((uint)local_c & 2) == 0) {
          iVar13 = (int)(((longlong)(local_8 - iVar15) * (longlong)(GridMaxZ - iVar14)) /
                        (longlong)(local_2c - iVar14));
          iVar16 = GridMaxZ;
        }
        else {
          iVar13 = (int)(((longlong)(local_8 - iVar15) * (longlong)(GridMinZ - iVar14)) /
                        (longlong)(local_2c - iVar14));
          iVar16 = GridMinZ;
        }
        iVar13 = iVar13 + iVar15;
      }
      else {
        iVar16 = (int)(((longlong)(local_2c - iVar14) * (longlong)(GridMaxX - iVar15)) /
                      (longlong)(local_8 - iVar15)) + iVar14;
        iVar13 = GridMaxX;
      }
    }
    else {
      iVar16 = (int)(((longlong)(local_2c - iVar14) * (longlong)(GridMinX - iVar15)) /
                    (longlong)(local_8 - iVar15)) + iVar14;
      iVar13 = GridMinX;
    }
    if (local_c == (float)local_1c) {
      local_1c = TerrainOutCode(iVar13,iVar16);
      iVar14 = iVar16;
      iVar15 = iVar13;
      local_18 = iVar13;
    }
    else {
      local_28 = TerrainOutCode(iVar13,iVar16);
      local_2c = iVar16;
      local_8 = iVar13;
    }
  }
  local_8 = local_8 - iVar15;
  iVar16 = local_2c - iVar14;
  local_14 = fVar10;
  if (fVar10 < 0.0) {
    local_8 = -local_8;
    local_30 = -1;
    local_24 = -local_24;
    local_14 = -fVar10;
  }
  local_10 = fVar12;
  if (fVar12 < 0.0) {
    iVar16 = -iVar16;
    local_34 = -1;
    local_20 = -local_20;
    local_10 = -fVar12;
  }
  uVar17 = (undefined4)((ulonglong)dVar1 >> 0x20);
  uVar18 = (undefined4)((ulonglong)dVar2 >> 0x20);
  if (local_14 <= local_10) {
    local_c = (0.5 - local_20) * local_14 - (0.5 - local_24) * local_10;
    while (-1 < iVar16) {
      iVar16 = iVar16 + -1;
      iVar13 = (*param_3)(iVar15,iVar14);
      if (iVar13 != 0) goto LAB_0051e89c;
      if (0.0 < local_c) {
        iVar15 = iVar15 + local_30;
        local_c = local_c - local_10;
        iVar13 = (*param_3)(iVar15,iVar14);
        local_18 = iVar15;
        if (iVar13 != 0) goto LAB_0051e865;
      }
      iVar14 = iVar14 + local_34;
      local_c = local_c + local_14;
    }
  }
  else {
    local_c = (0.5 - local_24) * local_10 - (0.5 - local_20) * local_14;
    while (-1 < local_8) {
      local_8 = local_8 + -1;
      iVar16 = (*param_3)(iVar15,iVar14);
      if (iVar16 != 0) {
LAB_0051e865:
        VVar3._4_8_ = (double)fVar8;
        VVar3.x._0_4_ = uVar17;
        VVar3.y._4_4_ = SUB84(dVar2,0);
        VVar3.z._0_4_ = uVar18;
        VVar3.z._4_4_ = fVar10;
        VVar5.y = fVar12;
        VVar5.x = fVar11;
        VVar5.z = unaff_EDI;
        ChangeIntersectionH(local_18,SUB84(dVar1,0),VVar3,VVar5,unaff_ESI);
        return 1;
      }
      if (0.0 < local_c) {
        iVar14 = iVar14 + local_34;
        local_c = local_c - local_14;
        iVar16 = (*param_3)(iVar15,iVar14);
        if (iVar16 != 0) {
LAB_0051e89c:
          VVar4._4_8_ = (double)fVar8;
          VVar4.x._0_4_ = uVar17;
          VVar4.y._4_4_ = SUB84(dVar2,0);
          VVar4.z._0_4_ = uVar18;
          VVar4.z._4_4_ = fVar10;
          VVar6.y = fVar12;
          VVar6.x = fVar11;
          VVar6.z = unaff_EDI;
          ChangeIntersectionV(iVar14,SUB84(dVar1,0),VVar4,VVar6,unaff_ESI);
          return 1;
        }
      }
      iVar15 = iVar15 + local_30;
      local_c = local_c + local_10;
      local_18 = iVar15;
    }
  }
  return 0;
}
