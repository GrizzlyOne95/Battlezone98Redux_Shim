/*
 * Entry: 004562a0
 * Name: FindPath
 * Namespace: Global
 * Signature: PathPlan * FindPath(VECTOR_3D * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PathPlan * __cdecl FindPath(VECTOR_3D *param_1,VECTOR_3D *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  PathPoint *pPVar4;
  PathPoint *pPVar5;
  float fVar6;
  float fVar7;
  SINCOS SVar8;
  uchar uVar9;
  bool bVar10;
  uchar uVar11;
  DWORD DVar12;
  int iVar13;
  DWORD DVar14;
  float unaff_EBX;
  VECTOR_3D *unaff_ESI;
  PathPlan *pPVar15;
  VECTOR_3D_LONG *unaff_EDI;
  int iVar16;
  SINCOS SVar17;
  float fVar18;
  double dVar19;
  float local_b8;
  Strip *local_b4;
  VECTOR_3D local_90;
  VECTOR_3D local_84;
  float local_78;
  undefined4 local_74;
  Strip *local_70;
  PathPoint local_68;
  double local_58;
  double local_50;
  double local_48;
  
  local_90.x = param_1->x;
  local_90.y = param_1->y;
  local_90.z = param_1->z;
  fVar1 = param_2->x;
  fVar2 = param_2->y;
  fVar3 = param_2->z;
  randomizeCost = false;
  DVar12 = timeGetTime();
  pPVar15 = (PathPlan *)0x0;
  if (curPathingType == 3) {
    pPVar15 = MemoryPool::Alloc(&planPool);
    if (pPVar15 == (PathPlan *)0x0) {
      pPVar15 = (PathPlan *)0x0;
    }
    else {
      pPVar15 = PathPlan::PathPlan(pPVar15);
    }
    local_68.point.z = 0.0;
    local_68.point.x = 0.0;
    pPVar15->flags = 0;
    pPVar15->curPoint = 0;
    local_68.strip = (Strip *)0x0;
    local_68.seqNo = 0;
    std::vector<PathPoint,std::allocator<PathPoint>_>::push_back(&pPVar15->points,&local_68);
    std::vector<PathPoint,std::allocator<PathPoint>_>::push_back(&pPVar15->points,&local_68);
    if ((int)(pPVar15->points)._Mylast - (int)(pPVar15->points)._Myfirst >> 4 == 0) {
      _invalid_parameter_noinfo();
    }
    pPVar4 = (pPVar15->points)._Myfirst;
    if ((uint)((int)(pPVar15->points)._Mylast - (int)pPVar4 >> 4) < 2) {
      _invalid_parameter_noinfo();
    }
    pPVar5 = (pPVar15->points)._Myfirst;
    (pPVar4->point).x = local_90.x;
    (pPVar4->point).z = local_90.z;
    pPVar5[1].point.x = fVar1;
    fVar1 = pPVar5[1].point.x;
    pPVar5[1].point.z = fVar3;
    (pPVar15->goal).x = fVar1;
    (pPVar15->goal).z = pPVar5[1].point.z;
    return pPVar15;
  }
  uVar9 = CellRegion(local_90.x,local_90.z);
  iVar16 = 0;
  do {
    bVar10 = IsStraightPlan(local_90.x,local_90.z,fVar1,fVar3,curPathingTeam);
    if (bVar10) {
      pPVar15 = MemoryPool::Alloc(&planPool);
      if (pPVar15 == (PathPlan *)0x0) {
        pPVar15 = (PathPlan *)0x0;
      }
      else {
        pPVar15 = PathPlan::PathPlan(pPVar15);
      }
      local_68.point.z = 0.0;
      local_68.point.x = 0.0;
      pPVar15->flags = 0;
      pPVar15->curPoint = 0;
      local_68.strip = (Strip *)0x0;
      local_68.seqNo = 0;
      std::vector<PathPoint,std::allocator<PathPoint>_>::push_back(&pPVar15->points,&local_68);
      std::vector<PathPoint,std::allocator<PathPoint>_>::push_back(&pPVar15->points,&local_68);
      if ((int)(pPVar15->points)._Mylast - (int)(pPVar15->points)._Myfirst >> 4 == 0) {
        _invalid_parameter_noinfo();
      }
      pPVar4 = (pPVar15->points)._Myfirst;
      if ((uint)((int)(pPVar15->points)._Mylast - (int)pPVar4 >> 4) < 2) {
        _invalid_parameter_noinfo();
      }
      pPVar5 = (pPVar15->points)._Myfirst;
      (pPVar4->point).x = local_90.x;
      (pPVar4->point).z = local_90.z;
      pPVar5[1].point.x = fVar1;
      fVar1 = pPVar5[1].point.x;
      pPVar5[1].point.z = fVar3;
      (pPVar15->goal).x = fVar1;
      (pPVar15->goal).z = pPVar5[1].point.z;
      return pPVar15;
    }
    local_84.x = fVar1;
    local_84.y = fVar2;
    local_84.z = fVar3;
    if (((0 < iVar16) || (bVar10 = OnBlocked(&local_84), bVar10)) ||
       (uVar11 = CellRegion(local_84.x,local_84.z), uVar11 != uVar9)) {
      fVar7 = 1.0;
      fVar18 = local_90.x - fVar1;
      fVar6 = local_90.z - fVar3;
      SVar8.Cos = fVar6;
      SVar8.Sin = fVar18;
      SVar17.Cos = fVar6;
      SVar17.Sin = fVar18;
      if ((0 < iVar16) || ((ABS(fVar18) < 0.0001 && (SVar17 = SVar8, ABS(fVar6) < 0.0001)))) {
        iVar13 = rand();
        SVar17 = SinCos(((float)iVar13 * 6.103702e-05 - 1.0) * 3.1415927);
        fVar7 = Terrain.Grid_Size * 16.0;
      }
      local_b4 = (Strip *)SVar17.Cos;
      local_b8 = SVar17.Sin;
      local_74 = 0;
      local_68.point.z = 0.0;
      local_58 = (double)fVar1;
      local_50 = (double)fVar2;
      local_48 = (double)fVar3;
      local_78 = local_b8;
      local_70 = local_b4;
      local_68.point.x = local_b8;
      local_68.strip = local_b4;
      fVar18 = DistToCellRegion(SUB41(fVar7,0),unaff_EDI,unaff_ESI,unaff_EBX);
      if (fVar18 < fVar7) {
        dVar19 = rsqrt((double)(local_b8 * local_b8 + (float)local_b4 * (float)local_b4));
        fVar18 = (float)dVar19 * Terrain.Grid_Size * 0.5 + fVar18;
        local_84.x = local_b8 * fVar18 + local_84.x;
        local_84.z = fVar18 * (float)local_b4 + local_84.z;
        goto LAB_00456601;
      }
    }
    else {
LAB_00456601:
      if (pPVar15 != (PathPlan *)0x0) {
        if ((pPVar15->flags & 4) != 0) {
          pPVar15->flags = pPVar15->flags & 0xfffffffb;
          Search::Clean();
        }
        (**(code **)pPVar15->_padding_)();
      }
      pPVar15 = FindPath2(&local_90,&local_84);
      if ((pPVar15->flags & 1) == 0) break;
    }
    iVar16 = iVar16 + 1;
  } while (iVar16 < 0x10);
  DVar14 = timeGetTime();
  if (pPVar15 == (PathPlan *)0x0) {
    pPVar15 = MemoryPool::Alloc(&planPool);
    if (pPVar15 == (PathPlan *)0x0) {
      pPVar15 = (PathPlan *)0x0;
    }
    else {
      pPVar15 = PathPlan::PathPlan(pPVar15);
    }
    local_68.point.z = 0.0;
    local_68.point.x = 0.0;
    pPVar15->flags = 1;
    local_68.strip = (Strip *)0x0;
    local_68.seqNo = 0;
    std::vector<PathPoint,std::allocator<PathPoint>_>::push_back(&pPVar15->points,&local_68);
    std::vector<PathPoint,std::allocator<PathPoint>_>::push_back(&pPVar15->points,&local_68);
    if ((int)(pPVar15->points)._Mylast - (int)(pPVar15->points)._Myfirst >> 4 == 0) {
      _invalid_parameter_noinfo();
    }
    pPVar4 = (pPVar15->points)._Myfirst;
    if ((uint)((int)(pPVar15->points)._Mylast - (int)pPVar4 >> 4) < 2) {
      _invalid_parameter_noinfo();
    }
    pPVar5 = (pPVar15->points)._Myfirst;
    (pPVar4->point).x = local_90.x;
    (pPVar4->point).z = local_90.z;
    pPVar5[1].point.x = fVar1;
    fVar1 = pPVar5[1].point.x;
    pPVar5[1].point.z = fVar3;
    (pPVar15->goal).x = fVar1;
    (pPVar15->goal).z = pPVar5[1].point.z;
    pPVar15->curPoint = 0;
  }
  if (10 < (int)(DVar14 - DVar12)) {
    Trace("searchTime(%d): from(%0.2f,%0.2f) to(%0.2f,%0.2f)\n");
  }
  return pPVar15;
}
