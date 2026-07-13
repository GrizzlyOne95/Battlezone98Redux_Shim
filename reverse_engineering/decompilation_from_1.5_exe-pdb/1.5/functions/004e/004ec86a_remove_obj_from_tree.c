/*
 * Entry: 004ec86a
 * Name: remove_obj_from_tree
 * Namespace: Global
 * Signature: void remove_obj_from_tree(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl remove_obj_from_tree(_OBJ76 *param_1)

{
  _OBJ76 *p_Var1;
  _OBJ76 *p_Var2;
  int iVar3;
  int extraout_EDX;
  _OBJ76 *p_Var4;
  
  p_Var1 = obj_get_parent(param_1);
  if (p_Var1 == (_OBJ76 *)0x0) {
    iVar3 = 0;
  }
  else {
    iVar3 = p_Var1->counter - 1;
    p_Var4 = p_Var1->child;
    if (p_Var4 == param_1) {
      p_Var1->child = param_1->sibling;
    }
    else {
      do {
        p_Var2 = p_Var4;
        if (p_Var2 == (_OBJ76 *)0x0) goto LAB_004ec8be;
        p_Var4 = p_Var2->sibling;
      } while (p_Var2->sibling != param_1);
      p_Var2->sibling = param_1->sibling;
    }
  }
LAB_004ec8be:
  param_1->counter = param_1->counter - (short)iVar3;
  param_1->parent = (_OBJ76 *)0x0;
  param_1->sibling = (_OBJ76 *)0x0;
  p_Var4 = param_1->child;
  if (p_Var4 != (_OBJ76 *)0x0) {
    iVar3 = -iVar3;
    do {
      tree_add_dibs(p_Var4,iVar3,p_Var1);
      p_Var4 = p_Var4->sibling;
      iVar3 = extraout_EDX;
    } while (p_Var4 != (_OBJ76 *)0x0);
  }
  return;
}
