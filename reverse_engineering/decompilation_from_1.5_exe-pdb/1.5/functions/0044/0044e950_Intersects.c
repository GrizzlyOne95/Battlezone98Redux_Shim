/*
 * Entry: 0044e950
 * Name: Intersects
 * Namespace: Global
 * Signature: bool Intersects(Strip * param_1, Strip * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl Intersects(Strip *param_1,Strip *param_2)

{
  if ((((param_2->x0 < param_1->x1) && (param_1->x0 <= param_2->x1)) && (param_2->z0 < param_1->z1))
     && (param_1->z0 <= param_2->z1)) {
    return true;
  }
  return false;
}
