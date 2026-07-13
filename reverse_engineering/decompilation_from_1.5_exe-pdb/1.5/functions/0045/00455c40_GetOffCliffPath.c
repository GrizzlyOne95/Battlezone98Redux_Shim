/*
 * Entry: 00455c40
 * Name: GetOffCliffPath
 * Namespace: Global
 * Signature: PathPlan * GetOffCliffPath(VECTOR_2D * param_1, VECTOR_2D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

PathPlan * __cdecl GetOffCliffPath(VECTOR_2D *param_1,VECTOR_2D *param_2)

{
  float fVar1;
  PathPoint *pPVar2;
  PathPoint *pPVar3;
  Strip *pSVar4;
  float fVar5;
  float fVar6;
  PathPlan *pPVar7;
  VECTOR_2D *pVVar8;
  PathPlan *pPVar9;
  Strip **ppSVar10;
  Strip **local_14;
  PathPoint local_10;
  
  pVVar8 = param_1;
  pPVar7 = curFindPath;
  GetStrips(param_1->x - 50.0,param_1->z - 50.0,param_1->x + 50.0,param_1->z + 50.0,(int *)&param_1,
            &local_14);
  pPVar9 = MemoryPool::Alloc(&planPool);
  if (pPVar9 == (PathPlan *)0x0) {
    pPVar9 = (PathPlan *)0x0;
  }
  else {
    pPVar9 = PathPlan::PathPlan(pPVar9);
  }
  pPVar9->curPoint = 0;
  local_10.strip = (Strip *)0x0;
  local_10.point.z = 0.0;
  local_10.seqNo = 0;
  local_10.point.x = 0.0;
  pPVar9->flags = 4;
  std::vector<PathPoint,std::allocator<PathPoint>_>::push_back(&pPVar9->points,&local_10);
  std::vector<PathPoint,std::allocator<PathPoint>_>::push_back(&pPVar9->points,&local_10);
  if ((int)(pPVar9->points)._Mylast - (int)(pPVar9->points)._Myfirst >> 4 == 0) {
    _invalid_parameter_noinfo();
  }
  pPVar2 = (pPVar9->points)._Myfirst;
  if ((uint)((int)(pPVar9->points)._Mylast - (int)pPVar2 >> 4) < 2) {
    _invalid_parameter_noinfo();
  }
  ppSVar10 = local_14;
  compareStart.x = pVVar8->x;
  pPVar3 = (pPVar9->points)._Myfirst;
  (pPVar2->point).x = compareStart.x;
  (pPVar2->point).z = pVVar8->z;
  compareStart.z = (pPVar2->point).z;
  std::_Sort<Strip_*_*,int,bool_(__cdecl*)(Strip_*,Strip_*)>
            (local_14,local_14 + (int)((int)&param_1[-1].z + 3),
             (int)(local_14 + (int)((int)&param_1[-1].z + 3)) - (int)local_14 >> 2,CompareStrips);
  local_14 = (Strip **)0x0;
  curFindPath = pPVar9;
  if (0 < (int)param_1) {
    do {
      pSVar4 = *ppSVar10;
      ppSVar10 = ppSVar10 + 1;
      if (pSVar4 != startStrip) {
        fVar1 = materialCost[pSVar4->material & 0xff];
        if ((ushort)((ushort)((uint)pSVar4->material >> 0x10) & (ushort)_curPathingEnemies) != 0) {
          fVar1 = fVar1 + 2.0;
        }
        if (fVar1 != 99999.0) {
          fVar1 = (pPVar2->point).x;
          fVar5 = pSVar4->x0 * Terrain.Grid_Size + 1.0;
          fVar6 = pSVar4->x1 * Terrain.Grid_Size - 1.0;
          if ((fVar1 < fVar5) || (fVar5 = fVar1, fVar1 <= fVar6)) {
            fVar6 = fVar5;
          }
          pPVar3[1].point.x = fVar6;
          fVar1 = (pPVar2->point).z;
          fVar5 = pSVar4->z0 * Terrain.Grid_Size + 1.0;
          fVar6 = pSVar4->z1 * Terrain.Grid_Size - 1.0;
          if ((fVar1 < fVar5) || (fVar5 = fVar1, fVar1 <= fVar6)) {
            fVar6 = fVar5;
          }
          pPVar3[1].point.z = fVar6;
          FindShortPath(pPVar9);
          if (pPVar9->flags == 0) {
            curFindPath = pPVar7;
            return pPVar9;
          }
        }
      }
      local_14 = (Strip **)((int)local_14 + 1);
      if ((int)param_1 <= (int)local_14) {
        curFindPath = pPVar7;
        return pPVar9;
      }
    } while( true );
  }
  curFindPath = pPVar7;
  return pPVar9;
}
