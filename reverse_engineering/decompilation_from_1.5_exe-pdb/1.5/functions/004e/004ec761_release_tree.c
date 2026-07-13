/*
 * Entry: 004ec761
 * Name: release_tree
 * Namespace: Global
 * Signature: void release_tree(_OBJ76 * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl release_tree(_OBJ76 *param_1,char *param_2)

{
  for (; param_1 != (_OBJ76 *)0x0; param_1 = param_1->sibling) {
    param_1->counter = param_1->counter - 1;
    if (param_1->child != (_OBJ76 *)0x0) {
      release_tree(param_1->child,param_2);
    }
  }
  return;
}
