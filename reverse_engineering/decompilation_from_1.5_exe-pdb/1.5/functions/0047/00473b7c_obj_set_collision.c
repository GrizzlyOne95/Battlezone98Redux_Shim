/*
 * Entry: 00473b7c
 * Name: obj_set_collision
 * Namespace: Global
 * Signature: void obj_set_collision(_OBJ76 * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl obj_set_collision(_OBJ76 *param_1,long param_2)

{
  param_1->flags = param_1->flags ^ (param_1->flags ^ param_2) & 0xf000;
  return;
}
