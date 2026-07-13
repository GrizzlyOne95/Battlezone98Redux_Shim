/*
 * Entry: 004ec6f0
 * Name: remove_obj
 * Namespace: Global
 * Signature: void remove_obj(_OBJ76 * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl remove_obj(_OBJ76 *param_1,char *param_2)

{
  _OBJ76 *p_Var1;
  _OBJ76 *p_Var2;
  _OBJ76 *p_Var3;
  ushort uVar4;
  
  if (param_1 != (_OBJ76 *)0x0) {
    p_Var1 = param_1->parent;
    uVar4 = 1;
    if (p_Var1 != (_OBJ76 *)0x0) {
      uVar4 = p_Var1->counter;
      p_Var2 = p_Var1->child;
      if (p_Var2 == param_1) {
        p_Var1->child = param_1->sibling;
      }
      else {
        do {
          p_Var3 = p_Var2;
          if (p_Var3 == (_OBJ76 *)0x0) goto LAB_004ec740;
          p_Var2 = p_Var3->sibling;
        } while (p_Var3->sibling != param_1);
        p_Var3->sibling = param_1->sibling;
      }
    }
LAB_004ec740:
    param_1->parent = (_OBJ76 *)0x0;
    param_1->sibling = (_OBJ76 *)0x0;
    remove_tree(param_1,1,uVar4,p_Var1,param_2);
  }
  return;
}
