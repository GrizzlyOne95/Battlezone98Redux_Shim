/*
 * Entry: 004ec793
 * Name: release_obj
 * Namespace: Global
 * Signature: void release_obj(_OBJ76 * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl release_obj(_OBJ76 *param_1,char *param_2)

{
  if (param_1 != (_OBJ76 *)0x0) {
    if (param_1->counter < 2) {
      remove_obj(param_1,param_2);
    }
    else {
      param_1->counter = param_1->counter - 1;
      release_tree(param_1->child,param_2);
    }
  }
  return;
}
