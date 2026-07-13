/*
 * Entry: 004510f0
 * Name: std::fill<PathPoint_*,PathPoint>
 * Namespace: std
 * Signature: void fill<PathPoint_*,PathPoint>(PathPoint * param_1, PathPoint * param_2, PathPoint * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::fill<PathPoint_*,PathPoint>(PathPoint *param_1,PathPoint *param_2,PathPoint *param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    (param_1->point).x = (param_3->point).x;
    (param_1->point).z = (param_3->point).z;
    param_1->strip = param_3->strip;
    param_1->seqNo = param_3->seqNo;
  }
  return;
}
