/*
 * Entry: 004508e0
 * Name: std::allocator<PathPoint>::allocate
 * Namespace: std::allocator<PathPoint>
 * Signature: PathPoint * allocate(allocator<PathPoint> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PathPoint * __thiscall std::allocator<PathPoint>::allocate(allocator<PathPoint> *this,uint param_1)

{
  PathPoint *pPVar1;
  
  pPVar1 = _Allocate<PathPoint>(param_1,(PathPoint *)0x0);
  return pPVar1;
}
