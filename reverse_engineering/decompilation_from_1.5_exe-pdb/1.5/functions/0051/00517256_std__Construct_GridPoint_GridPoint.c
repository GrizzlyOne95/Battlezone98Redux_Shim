/*
 * Entry: 00517256
 * Name: std::_Construct<GridPoint,GridPoint>
 * Namespace: std
 * Signature: void _Construct<GridPoint,GridPoint>(GridPoint * param_1, GridPoint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Construct<GridPoint,GridPoint>(GridPoint *param_1,GridPoint *param_2)

{
  if (param_1 != (GridPoint *)0x0) {
    param_1->x = param_2->x;
    param_1->y = param_2->y;
  }
  return;
}
