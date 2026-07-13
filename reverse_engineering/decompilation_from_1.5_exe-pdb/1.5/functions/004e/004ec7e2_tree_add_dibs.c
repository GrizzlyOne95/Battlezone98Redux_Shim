/*
 * Entry: 004ec7e2
 * Name: tree_add_dibs
 * Namespace: Global
 * Signature: void tree_add_dibs(_OBJ76 * param_1, int param_2, _OBJ76 * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl tree_add_dibs(_OBJ76 *param_1,int param_2,_OBJ76 *param_3)

{
  _OBJ76 *p_Var1;
  
  if (param_1 != (_OBJ76 *)0x0) {
    p_Var1 = param_1->child;
    param_1->counter = param_1->counter + (short)param_2;
    for (; p_Var1 != (_OBJ76 *)0x0; p_Var1 = p_Var1->sibling) {
      tree_add_dibs(p_Var1,param_2,param_3);
    }
  }
  return;
}
