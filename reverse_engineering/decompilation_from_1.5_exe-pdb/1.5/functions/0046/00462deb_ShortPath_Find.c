/*
 * Entry: 00462deb
 * Name: ShortPath::Find
 * Namespace: ShortPath
 * Signature: void Find(PathPlan * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ShortPath::Find(PathPlan *param_1)

{
  PathPoint *pPVar1;
  
  pPVar1 = std::vector<PathPoint,std::allocator<PathPoint>_>::operator[](&param_1->points,0);
  start.x = (pPVar1->point).x;
  start.z = (pPVar1->point).z;
  pPVar1 = std::vector<PathPoint,std::allocator<PathPoint>_>::operator[](&param_1->points,1);
  goal.x = (pPVar1->point).x;
  goal.z = (pPVar1->point).z;
  if (ABS(goal.x - start.x) * ABS(goal.z - start.z) <= 10000.0) {
    param_1->flags = 0x10;
    path = param_1;
    Extents::Init();
    Search();
    Make();
    Extents::Clean();
    return;
  }
  return;
}
