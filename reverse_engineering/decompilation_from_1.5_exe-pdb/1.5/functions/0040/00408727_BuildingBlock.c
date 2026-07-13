/*
 * Entry: 00408727
 * Name: BuildingBlock
 * Namespace: Global
 * Signature: void BuildingBlock(int param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl BuildingBlock(int param_1,int param_2,int param_3)

{
  VECTOR_2D *pVVar1;
  int iVar2;
  VECTOR_2D VVar3;
  VECTOR_2D VVar4;
  VECTOR_2D VVar5;
  VECTOR_2D VVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  int iVar10;
  list<AiTask_*,std::allocator<AiTask_*>_> *plVar11;
  VECTOR_2D *pVVar12;
  _func___cdecl_SObject_ptr *p_Var13;
  VECTOR_2D VVar14;
  VECTOR_2D VVar15;
  VECTOR_2D VVar16;
  float fVar17;
  float fVar18;
  VECTOR_2D local_2c;
  float local_24;
  float local_20;
  float local_18;
  int local_14;
  float local_10;
  int local_c;
  
  if (blockVertCount != 0) {
    local_c = 0;
    p_Var13 = (&EmptyMission::classEmptyMission.m_pfnCreateObject)[blockVertCount * 2];
    plVar11 = (&AiTask::tasklist)[blockVertCount * 2];
    local_14 = -1;
    fVar8 = ((float)param_2 + 0.5) * Terrain.Grid_Size;
    fVar9 = ((float)param_3 + 0.5) * Terrain.Grid_Size;
    fVar7 = Terrain.Grid_Size * 0.5;
    local_10 = -3.4028235e+38;
    iVar10 = -1;
    if (0 < blockVertCount) {
      pVVar12 = blockVertArray;
      do {
        VVar15.z = (float)plVar11;
        VVar15.x = (float)p_Var13;
        VVar14 = Vec2D_Subtract(*pVVar12,VVar15);
        VVar15 = Vec2D_Normalize(VVar14);
        VVar14.z = fVar9;
        VVar14.x = fVar8;
        VVar16.z = (float)plVar11;
        VVar16.x = (float)p_Var13;
        VVar14 = Vec2D_Subtract(VVar14,VVar16);
        local_20 = VVar15.z;
        local_2c.z = VVar14.z;
        fVar18 = (local_2c.z * -VVar15.x + local_2c.x * local_20) - fVar7;
        if (0.0 < fVar18) {
          return;
        }
        if (local_10 < fVar18) {
          local_14 = local_c;
          local_10 = fVar18;
        }
        p_Var13 = (_func___cdecl_SObject_ptr *)pVVar12->x;
        plVar11 = (list<AiTask_*,std::allocator<AiTask_*>_> *)pVVar12->z;
        local_c = local_c + 1;
        pVVar12 = pVVar12 + 1;
        iVar10 = local_14;
        local_2c = VVar14;
      } while (local_c < blockVertCount);
    }
    if (-fVar7 < local_10) {
      iVar2 = blockVertCount;
      if (0 < iVar10) {
        iVar2 = iVar10;
      }
      pVVar12 = blockVertArray + iVar2 + -1;
      pVVar1 = blockVertArray + iVar10;
      VVar14 = Vec2D_Subtract(*pVVar1,*pVVar12);
      VVar3.z = fVar9;
      VVar3.x = fVar8;
      VVar16 = Vec2D_Subtract(VVar3,*pVVar12);
      local_20 = VVar14.z;
      local_24 = VVar14.x;
      local_2c.z = VVar16.z;
      fVar18 = local_2c.z * local_20 + local_2c.x * local_24;
      if (fVar18 < 0.0 == (fVar18 == 0.0)) {
        VVar14 = Vec2D_Subtract(*pVVar12,*pVVar1);
        VVar4.z = fVar9;
        VVar4.x = fVar8;
        VVar15 = Vec2D_Subtract(VVar4,*pVVar1);
        local_20 = VVar14.z;
        local_24 = VVar14.x;
        local_2c.x = VVar16.x;
        local_2c.z = VVar15.z;
        fVar18 = local_2c.z * local_20 + local_2c.x * local_24;
        if (fVar18 < 0.0 == (fVar18 == 0.0)) goto LAB_00408917;
        fVar18 = blockVertArray[iVar10].z;
        fVar17 = pVVar1->x;
      }
      else {
        fVar18 = blockVertArray[iVar2 + -1].z;
        fVar17 = pVVar12->x;
      }
      VVar5.z = fVar9;
      VVar5.x = fVar8;
      VVar6.z = fVar18;
      VVar6.x = fVar17;
      VVar14 = Vec2D_Subtract(VVar5,VVar6);
      local_18 = VVar14.z;
      if (fVar7 * fVar7 < local_18 * local_18 + fVar8 * fVar8) {
        return;
      }
    }
  }
LAB_00408917:
  cellType[param_1] = cellType[param_1] | 0xb;
  return;
}
