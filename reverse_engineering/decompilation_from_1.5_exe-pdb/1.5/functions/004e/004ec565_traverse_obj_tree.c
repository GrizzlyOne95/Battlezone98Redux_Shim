/*
 * Entry: 004ec565
 * Name: traverse_obj_tree
 * Namespace: Global
 * Signature: int traverse_obj_tree(_func___cdecl_int__OBJ76_ptr_void_ptr * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl traverse_obj_tree(_func___cdecl_int__OBJ76_ptr_void_ptr *param_1,void *param_2)

{
  int iVar1;
  
  iVar1 = obj_traversal_func(obj_tree_head,param_1,param_2);
  return iVar1;
}
