/*
 * Entry: 004ecacf
 * Name: obj_clear_flag
 * Namespace: Global
 * Signature: void obj_clear_flag(_OBJ76 * param_1, ulong param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl obj_clear_flag(_OBJ76 *param_1,ulong param_2)

{
  if (param_1 != (_OBJ76 *)0x0) {
    param_1->flags = param_1->flags & ~param_2;
    if (param_1->child != (_OBJ76 *)0x0) {
      clear_flags_in_subtree(param_1->child,param_2);
    }
  }
  return;
}
