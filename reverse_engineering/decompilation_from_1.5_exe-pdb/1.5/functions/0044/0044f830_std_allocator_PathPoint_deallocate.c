/*
 * Entry: 0044f830
 * Name: std::allocator<PathPoint>::deallocate
 * Namespace: std::allocator<PathPoint>
 * Signature: void deallocate(allocator<PathPoint> * this, PathPoint * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<PathPoint>::deallocate(allocator<PathPoint> *this,PathPoint *param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
