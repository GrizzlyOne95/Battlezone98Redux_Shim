/*
 * Entry: 004ec4fc
 * Name: obj_traversal_func
 * Namespace: Global
 * Signature: int obj_traversal_func(_OBJ76 * param_1, _func___cdecl_int__OBJ76_ptr_void_ptr * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
obj_traversal_func(_OBJ76 *param_1,_func___cdecl_int__OBJ76_ptr_void_ptr *param_2,void *param_3)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 1;
  iVar1 = (*param_2)(param_1,param_3);
  if (iVar1 != 0) {
    iVar1 = iVar2;
    if (param_1->child != (_OBJ76 *)0x0) {
      iVar1 = obj_traversal_func(param_1->child,param_2,param_3);
    }
    if (param_1->sibling != (_OBJ76 *)0x0) {
      if (iVar1 == 0) {
        return 0;
      }
      iVar2 = obj_traversal_func(param_1->sibling,param_2,param_3);
    }
    if ((iVar1 != 0) && (iVar2 != 0)) {
      return 1;
    }
  }
  return 0;
}
