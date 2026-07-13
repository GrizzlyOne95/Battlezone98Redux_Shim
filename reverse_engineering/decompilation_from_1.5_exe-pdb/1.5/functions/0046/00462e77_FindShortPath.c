/*
 * Entry: 00462e77
 * Name: FindShortPath
 * Namespace: Global
 * Signature: void FindShortPath(PathPlan * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FindShortPath(PathPlan *param_1)

{
  PathPoint *pPVar1;
  
  pPVar1 = std::vector<PathPoint,std::allocator<PathPoint>_>::operator[](&param_1->points,0);
  ShortPath::start.x = (pPVar1->point).x;
  ShortPath::start.z = (pPVar1->point).z;
  pPVar1 = std::vector<PathPoint,std::allocator<PathPoint>_>::operator[](&param_1->points,1);
  ShortPath::goal.x = (pPVar1->point).x;
  ShortPath::goal.z = (pPVar1->point).z;
  if (ABS(ShortPath::goal.x - ShortPath::start.x) * ABS(ShortPath::goal.z - ShortPath::start.z) <=
      10000.0) {
    param_1->flags = 0x10;
    ShortPath::path = param_1;
    ShortPath::Extents::Init();
    ShortPath::Search();
    ShortPath::Make();
    ShortPath::Extents::Clean();
    return;
  }
  return;
}
