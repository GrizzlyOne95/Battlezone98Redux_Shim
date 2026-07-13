/*
 * Entry: 004ec57c
 * Name: i_got_dibs_on_obj
 * Namespace: Global
 * Signature: void i_got_dibs_on_obj(_OBJ76 * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl i_got_dibs_on_obj(_OBJ76 *param_1,char *param_2)

{
  if (param_1 != (_OBJ76 *)0x0) {
    if (in_child != 0) {
      do {
        param_1->counter = param_1->counter + 1;
        i_got_dibs_on_obj(param_1->child,param_2);
        param_1 = param_1->sibling;
      } while (param_1 != (_OBJ76 *)0x0);
      return;
    }
    param_1->counter = param_1->counter + 1;
    in_child = 1;
    i_got_dibs_on_obj(param_1->child,param_2);
    in_child = 0;
  }
  return;
}
