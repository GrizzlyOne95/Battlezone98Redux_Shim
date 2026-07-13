/*
 * Entry: 004ec681
 * Name: remove_tree
 * Namespace: Global
 * Signature: void remove_tree(_OBJ76 * param_1, long param_2, ushort param_3, _OBJ76 * param_4, char * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl remove_tree(_OBJ76 *param_1,long param_2,ushort param_3,_OBJ76 *param_4,char *param_5)

{
  _OBJ76 *unaff_EDI;
  
  if (param_1->child != (_OBJ76 *)0x0) {
    remove_tree(param_1->child,param_2 + 1,param_3,param_4,param_5);
  }
  if ((param_1->sibling != (_OBJ76 *)0x0) && (1 < param_2)) {
    remove_tree(param_1->sibling,param_2 + 1,param_3,param_4,param_5);
  }
  param_1->counter = param_1->counter - param_3;
  (param_1->objHandle).handle = 0;
  param_1->gravestone = 1;
  if (param_1->counter == 0) {
    delete_obj(unaff_EDI);
  }
  return;
}
