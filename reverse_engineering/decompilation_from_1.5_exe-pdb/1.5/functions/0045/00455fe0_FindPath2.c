/*
 * Entry: 00455fe0
 * Name: FindPath2
 * Namespace: Global
 * Signature: PathPlan * FindPath2(VECTOR_3D * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PathPlan * __cdecl FindPath2(VECTOR_3D *param_1,VECTOR_3D *param_2)

{
  float fVar1;
  float fVar2;
  PathPoint *pPVar3;
  PathPoint *pPVar4;
  uchar uVar5;
  uchar uVar6;
  PathPlan *pPVar7;
  PathPoint *pPVar8;
  PathPlan *pPVar9;
  PathPlan *pPVar10;
  PathPlan *unaff_ESI;
  PathPoint *pPVar11;
  PathPlan *unaff_EDI;
  float fVar12;
  float fVar13;
  PathPoint local_10;
  
  fVar12 = param_1->x;
  fVar1 = param_1->z;
  fVar13 = param_2->x;
  fVar2 = param_2->z;
  startStrip = FindStrip((VECTOR_3D *)unaff_EDI);
  goalStrip = FindStrip((VECTOR_3D *)unaff_EDI);
  pPVar7 = MemoryPool::Alloc(&planPool);
  if (pPVar7 == (PathPlan *)0x0) {
    pPVar7 = (PathPlan *)0x0;
  }
  else {
    pPVar7 = PathPlan::PathPlan(pPVar7);
  }
  pPVar7->curPoint = 0;
  local_10.strip = (Strip *)0x0;
  local_10.point.z = 0.0;
  local_10.seqNo = 0;
  local_10.point.x = 0.0;
  pPVar7->flags = 4;
  std::vector<PathPoint,std::allocator<PathPoint>_>::push_back(&pPVar7->points,&local_10);
  std::vector<PathPoint,std::allocator<PathPoint>_>::push_back(&pPVar7->points,&local_10);
  if ((int)(pPVar7->points)._Mylast - (int)(pPVar7->points)._Myfirst >> 4 == 0) {
    _invalid_parameter_noinfo();
  }
  pPVar3 = (pPVar7->points)._Myfirst;
  if ((uint)((int)(pPVar7->points)._Mylast - (int)pPVar3 >> 4) < 2) {
    _invalid_parameter_noinfo();
  }
  pPVar4 = (pPVar7->points)._Myfirst;
  (pPVar3->point).x = fVar12;
  pPVar11 = pPVar4 + 1;
  (pPVar3->point).z = fVar1;
  (pPVar11->point).x = fVar13;
  pPVar4[1].point.z = fVar2;
  uVar5 = CellRegion(fVar12,fVar1);
  uVar6 = CellRegion(fVar13,fVar2);
  if ((((startStrip == (Strip *)0x0) || (goalStrip == (Strip *)0x0)) || (uVar5 == '\0')) ||
     ((uVar6 == '\0' || (uVar5 != uVar6)))) {
    pPVar7->flags = 1;
    (pPVar7->goal).x = (pPVar11->point).x;
    (pPVar7->goal).z = pPVar4[1].point.z;
    return pPVar7;
  }
  if (startStrip != goalStrip) {
    pPVar10 = (PathPlan *)0x0;
    curFindPath = pPVar7;
    fVar13 = MaterialCost(startStrip->material);
    if (fVar13 == 99999.0) {
      pPVar10 = GetOffCliffPath(&pPVar3->point,&pPVar11->point);
      if (pPVar10->flags == 0) {
        pPVar8 = std::vector<PathPoint,std::allocator<PathPoint>_>::back(&pPVar10->points);
        (pPVar3->point).x = (pPVar8->point).x;
        (pPVar3->point).z = (pPVar8->point).z;
      }
      else {
        (pPVar3->point).x = fVar12;
        (pPVar3->point).z = fVar1;
      }
      (pPVar3->point).x = (pPVar3->point).x + 0.1;
      (pPVar3->point).z = (pPVar3->point).z + 0.1;
    }
    pPVar7->flags = 4;
    curNode = (Strip *)0x0;
    (pPVar3->point).x = Terrain.Grid_Scale * (pPVar3->point).x;
    (pPVar3->point).z = Terrain.Grid_Scale * (pPVar3->point).z;
    (pPVar11->point).x = (pPVar11->point).x * Terrain.Grid_Scale;
    pPVar4[1].point.z = pPVar4[1].point.z * Terrain.Grid_Scale;
    Search::path = pPVar7;
    A_Star();
    Search::Clean();
    pPVar9 = pPVar7;
    if (pPVar10 != (PathPlan *)0x0) {
      pPVar9 = Splice(unaff_EDI,unaff_ESI);
      FreePath(pPVar10);
      FreePath(pPVar7);
    }
    curFindPath = (PathPlan *)0x0;
    return pPVar9;
  }
  fVar12 = MaterialCost(startStrip->material);
  if (fVar12 != 99999.0) {
    pPVar7->flags = 0;
    pPVar7->curPoint = 0;
    (pPVar7->goal).x = (pPVar11->point).x;
    (pPVar7->goal).z = pPVar4[1].point.z;
    return pPVar7;
  }
  pPVar7->flags = 1;
  pPVar7->curPoint = 0;
  (pPVar7->goal).x = (pPVar11->point).x;
  (pPVar7->goal).z = pPVar4[1].point.z;
  return pPVar7;
}
