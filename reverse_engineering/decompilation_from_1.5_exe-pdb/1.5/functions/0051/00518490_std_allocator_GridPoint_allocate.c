/*
 * Entry: 00518490
 * Name: std::allocator<GridPoint>::allocate
 * Namespace: std::allocator<GridPoint>
 * Signature: GridPoint * allocate(allocator<GridPoint> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GridPoint * __thiscall std::allocator<GridPoint>::allocate(allocator<GridPoint> *this,uint param_1)

{
  GridPoint *pGVar1;
  
  pGVar1 = _Allocate<GridPoint>(param_1,(GridPoint *)0x0);
  return pGVar1;
}
