/*
 * Entry: 00517014
 * Name: std::allocator<GridPoint>::deallocate
 * Namespace: std::allocator<GridPoint>
 * Signature: void deallocate(allocator<GridPoint> * this, GridPoint * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<GridPoint>::deallocate(allocator<GridPoint> *this,GridPoint *param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
