/*
 * Entry: 0047225e
 * Name: obj_get_collision
 * Namespace: Global
 * Signature: long obj_get_collision(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl obj_get_collision(_OBJ76 *param_1)

{
  return param_1->flags & 0xf000;
}
