/*
 * Entry: 00482bd4
 * Name: get_obj_team
 * Namespace: Global
 * Signature: int get_obj_team(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl get_obj_team(_OBJ76 *param_1)

{
  return *(ushort *)((int)&param_1->flags + 2) & 0xf;
}
