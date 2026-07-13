/*
 * Entry: 0052dc64
 * Name: Explosion_GetOwner
 * Namespace: Global
 * Signature: _OBJ76 * Explosion_GetOwner(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_OBJ76 * __cdecl Explosion_GetOwner(_OBJ76 *param_1)

{
  return *(_OBJ76 **)((int)param_1->class_ptr + 0x14);
}
