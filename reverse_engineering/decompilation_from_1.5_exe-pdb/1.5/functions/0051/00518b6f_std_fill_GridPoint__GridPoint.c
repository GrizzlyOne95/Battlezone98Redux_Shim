/*
 * Entry: 00518b6f
 * Name: std::fill<GridPoint_*,GridPoint>
 * Namespace: std
 * Signature: void fill<GridPoint_*,GridPoint>(GridPoint * param_1, GridPoint * param_2, GridPoint * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::fill<GridPoint_*,GridPoint>(GridPoint *param_1,GridPoint *param_2,GridPoint *param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    param_1->x = param_3->x;
    param_1->y = param_3->y;
  }
  return;
}
