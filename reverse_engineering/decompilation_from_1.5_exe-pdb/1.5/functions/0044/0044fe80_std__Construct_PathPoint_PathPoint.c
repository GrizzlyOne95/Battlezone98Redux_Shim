/*
 * Entry: 0044fe80
 * Name: std::_Construct<PathPoint,PathPoint>
 * Namespace: std
 * Signature: void _Construct<PathPoint,PathPoint>(PathPoint * param_1, PathPoint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Construct<PathPoint,PathPoint>(PathPoint *param_1,PathPoint *param_2)

{
  if (param_1 != (PathPoint *)0x0) {
    (param_1->point).x = (param_2->point).x;
    (param_1->point).z = (param_2->point).z;
    param_1->strip = param_2->strip;
    param_1->seqNo = param_2->seqNo;
  }
  return;
}
