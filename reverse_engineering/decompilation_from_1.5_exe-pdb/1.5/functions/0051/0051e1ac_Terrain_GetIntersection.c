/*
 * Entry: 0051e1ac
 * Name: Terrain_GetIntersection
 * Namespace: Global
 * Signature: int Terrain_GetIntersection(VECTOR_3D_LONG param_1, VECTOR_3D param_2, float * param_3, VECTOR_3D * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
Terrain_GetIntersection(VECTOR_3D_LONG param_1,VECTOR_3D param_2,float *param_3,VECTOR_3D *param_4)

{
  double dVar1;
  double dVar2;
  double dVar3;
  VECTOR_3D_LONG VVar4;
  VECTOR_3D_LONG VVar5;
  VECTOR_3D_LONG VVar6;
  VECTOR_3D_LONG VVar7;
  VECTOR_3D VVar8;
  VECTOR_3D VVar9;
  VECTOR_3D VVar10;
  VECTOR_3D VVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int unaff_EDI;
  int local_44;
  int local_34;
  int local_30;
  uint local_2c;
  float local_28;
  float local_24;
  uint local_20;
  float local_1c;
  float local_18;
  long local_14;
  float local_10;
  long local_c;
  long local_8;
  
  fVar12 = (float)param_1.x * Terrain.Grid_Scale;
  dVar1 = (double)fVar12;
  dVar2 = (double)((float)param_1.y * Terrain.Grid_Scale);
  fVar13 = (float)param_1.z * Terrain.Grid_Scale;
  dVar3 = (double)fVar13;
  fVar14 = param_2.x * Terrain.Grid_Scale;
  fVar15 = param_2.y * Terrain.Grid_Scale;
  fVar16 = Terrain.Grid_Scale * param_2.z;
  Set_Rounding(unaff_EDI);
  local_44 = (int)(longlong)ROUND(dVar1);
  iVar18 = local_44;
  local_14 = local_44;
  local_44 = (int)(longlong)ROUND(*param_3 * fVar14 + fVar12);
  iVar20 = local_44;
  local_8 = local_44;
  local_44 = (int)(longlong)ROUND(dVar3);
  iVar19 = local_44;
  local_44 = (int)(longlong)ROUND(*param_3 * fVar16 + fVar13);
  local_c = local_44;
  Set_Rounding(unaff_EDI);
  local_30 = 1;
  local_28 = (fVar12 - 0.5) - (float)iVar18;
  local_24 = (fVar13 - 0.5) - (float)iVar19;
  local_34 = 1;
  local_20 = TerrainOutCode(iVar18,iVar19);
  local_2c = TerrainOutCode(iVar20,local_44);
  if (local_2c != 0 || local_20 != 0) {
    do {
      if ((local_20 & local_2c) != 0) {
        return 0;
      }
      local_10 = (float)local_20;
      if (local_20 == 0) {
        local_10 = (float)local_2c;
      }
      if (((uint)local_10 & 8) == 0) {
        if (((uint)local_10 & 4) == 0) {
          if (((uint)local_10 & 2) == 0) {
            iVar17 = (int)(((longlong)(local_8 - iVar18) * (longlong)(GridMaxZ - iVar19)) /
                          (longlong)(local_c - iVar19));
            iVar20 = GridMaxZ;
          }
          else {
            iVar17 = (int)(((longlong)(local_8 - iVar18) * (longlong)(GridMinZ - iVar19)) /
                          (longlong)(local_c - iVar19));
            iVar20 = GridMinZ;
          }
          iVar17 = iVar17 + iVar18;
        }
        else {
          iVar20 = (int)(((longlong)(local_c - iVar19) * (longlong)(GridMaxX - iVar18)) /
                        (longlong)(local_8 - iVar18)) + iVar19;
          iVar17 = GridMaxX;
        }
      }
      else {
        iVar20 = (int)(((longlong)(local_c - iVar19) * (longlong)(GridMinX - iVar18)) /
                      (longlong)(local_8 - iVar18)) + iVar19;
        iVar17 = GridMinX;
      }
      if (local_10 == (float)local_20) {
        local_20 = TerrainOutCode(iVar17,iVar20);
        iVar19 = iVar20;
        iVar18 = iVar17;
        local_14 = iVar17;
      }
      else {
        local_2c = TerrainOutCode(iVar17,iVar20);
        local_c = iVar20;
        local_8 = iVar17;
      }
    } while (local_2c != 0 || local_20 != 0);
  }
  local_8 = local_8 - iVar18;
  local_c = local_c - iVar19;
  local_1c = fVar14;
  if (fVar14 < 0.0) {
    local_8 = -local_8;
    local_30 = -1;
    local_28 = -local_28;
    local_1c = -fVar14;
  }
  local_18 = fVar16;
  if (fVar16 < 0.0) {
    local_c = -local_c;
    local_34 = -1;
    local_24 = -local_24;
    local_18 = -fVar16;
  }
  if (local_1c <= local_18) {
    local_10 = (0.5 - local_24) * local_1c - (0.5 - local_28) * local_18;
    while (-1 < local_c) {
      local_c = local_c + -1;
      VVar6.y = dVar2;
      VVar6.x = dVar1;
      VVar6.z = dVar3;
      VVar10.y = fVar15;
      VVar10.x = fVar14;
      VVar10.z = fVar16;
      iVar18 = PointGridIntersection(local_14,iVar19,VVar6,VVar10,param_3,param_4);
      if (iVar18 != 0) {
        return 1;
      }
      if (0.0 < local_10) {
        local_14 = local_14 + local_30;
        local_10 = local_10 - local_18;
        VVar7.y = dVar2;
        VVar7.x = dVar1;
        VVar7.z = dVar3;
        VVar11.y = fVar15;
        VVar11.x = fVar14;
        VVar11.z = fVar16;
        iVar18 = PointGridIntersection(local_14,iVar19,VVar7,VVar11,param_3,param_4);
        if (iVar18 != 0) {
          return 1;
        }
      }
      iVar19 = iVar19 + local_34;
      local_10 = local_10 + local_1c;
    }
  }
  else {
    local_10 = (0.5 - local_28) * local_18 - (0.5 - local_24) * local_1c;
    while (-1 < local_8) {
      local_8 = local_8 + -1;
      VVar4.y = dVar2;
      VVar4.x = dVar1;
      VVar4.z = dVar3;
      VVar8.y = fVar15;
      VVar8.x = fVar14;
      VVar8.z = fVar16;
      iVar18 = PointGridIntersection(local_14,iVar19,VVar4,VVar8,param_3,param_4);
      if (iVar18 != 0) {
        return 1;
      }
      if (0.0 < local_10) {
        local_10 = local_10 - local_1c;
        iVar19 = iVar19 + local_34;
        VVar5.y = dVar2;
        VVar5.x = dVar1;
        VVar5.z = dVar3;
        VVar9.y = fVar15;
        VVar9.x = fVar14;
        VVar9.z = fVar16;
        iVar18 = PointGridIntersection(local_14,iVar19,VVar5,VVar9,param_3,param_4);
        if (iVar18 != 0) {
          return 1;
        }
      }
      local_14 = local_14 + local_30;
      local_10 = local_10 + local_18;
    }
  }
  return 0;
}
