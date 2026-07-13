/*
 * Entry: 004ec817
 * Name: add_obj_to_tree
 * Namespace: Global
 * Signature: void add_obj_to_tree(_OBJ76 * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl add_obj_to_tree(_OBJ76 *param_1,_OBJ76 *param_2)

{
  _OBJ76 *extraout_ECX;
  int iVar1;
  int extraout_EDX;
  _OBJ76 *p_Var2;
  
  if (param_2 != (_OBJ76 *)0x0) {
    param_1->parent = param_2;
    param_1->sibling = param_2->child;
    param_2->child = param_1;
    p_Var2 = param_1->child;
    param_1->gravestone = param_2->gravestone;
    iVar1 = param_2->counter - 1;
    param_1->counter = param_1->counter + (short)iVar1;
    for (; p_Var2 != (_OBJ76 *)0x0; p_Var2 = p_Var2->sibling) {
      tree_add_dibs(p_Var2,iVar1,param_2);
      param_2 = extraout_ECX;
      iVar1 = extraout_EDX;
    }
  }
  return;
}
