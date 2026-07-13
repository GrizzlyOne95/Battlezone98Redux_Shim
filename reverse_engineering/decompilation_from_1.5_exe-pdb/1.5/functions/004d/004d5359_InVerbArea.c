/*
 * Entry: 004d5359
 * Name: InVerbArea
 * Namespace: Global
 * Signature: bool InVerbArea(tagPOINT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl InVerbArea(tagPOINT *param_1)

{
  if ((((btnX0 <= param_1->x) && (param_1->x <= btnX1)) && (btnY0 <= param_1->y)) &&
     (param_1->y <= btnY1)) {
    return true;
  }
  return false;
}
