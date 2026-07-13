/*
 * Entry: 004e9c50
 * Name: ClassRegisterSimulateFn
 * Namespace: Global
 * Signature: void ClassRegisterSimulateFn(OBJECT_CLASS_T param_1, _func___cdecl_void__OBJ76_ptr * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ClassRegisterSimulateFn(OBJECT_CLASS_T param_1,_func___cdecl_void__OBJ76_ptr *param_2)

{
  int iVar1;
  OBJECT_CLASS_T unaff_retaddr;
  
  iVar1 = ClassIDtoIndex(unaff_retaddr);
  funk[iVar1].simulate_fn = param_2;
  return;
}
