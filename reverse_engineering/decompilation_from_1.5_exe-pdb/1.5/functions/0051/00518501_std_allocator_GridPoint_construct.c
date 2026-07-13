/*
 * Entry: 00518501
 * Name: std::allocator<GridPoint>::construct
 * Namespace: std::allocator<GridPoint>
 * Signature: void construct(allocator<GridPoint> * this, GridPoint * param_1, GridPoint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<GridPoint>::construct
          (allocator<GridPoint> *this,GridPoint *param_1,GridPoint *param_2)

{
  _Construct<GridPoint,GridPoint>(param_1,param_2);
  return;
}
