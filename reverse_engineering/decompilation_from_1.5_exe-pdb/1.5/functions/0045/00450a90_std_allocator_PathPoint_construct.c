/*
 * Entry: 00450a90
 * Name: std::allocator<PathPoint>::construct
 * Namespace: std::allocator<PathPoint>
 * Signature: void construct(allocator<PathPoint> * this, PathPoint * param_1, PathPoint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<PathPoint>::construct
          (allocator<PathPoint> *this,PathPoint *param_1,PathPoint *param_2)

{
  if (param_1 != (PathPoint *)0x0) {
    (param_1->point).x = (param_2->point).x;
    (param_1->point).z = (param_2->point).z;
    param_1->strip = param_2->strip;
    param_1->seqNo = param_2->seqNo;
  }
  return;
}
