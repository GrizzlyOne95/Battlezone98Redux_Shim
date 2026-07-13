/*
 * Entry: 004eca3e
 * Name: set_flags_in_subtree
 * Namespace: Global
 * Signature: void set_flags_in_subtree(_OBJ76 * param_1, ulong param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl set_flags_in_subtree(_OBJ76 *param_1,ulong param_2)

{
  if (param_1->sibling != (_OBJ76 *)0x0) {
    set_flags_in_subtree(param_1->sibling,param_2);
  }
  if (param_1->child != (_OBJ76 *)0x0) {
    set_flags_in_subtree(param_1->child,param_2);
  }
  param_1->flags = param_1->flags | param_2;
  return;
}
