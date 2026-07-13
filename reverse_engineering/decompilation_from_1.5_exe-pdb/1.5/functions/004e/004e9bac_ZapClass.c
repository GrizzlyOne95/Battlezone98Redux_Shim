/*
 * Entry: 004e9bac
 * Name: ZapClass
 * Namespace: Global
 * Signature: void ZapClass(OBJECT_CLASS_T param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ZapClass(OBJECT_CLASS_T param_1,void *param_2)

{
  int iVar1;
  OBJECT_CLASS_T unaff_retaddr;
  
  if (param_2 != (void *)0x0) {
    iVar1 = ClassIDtoIndex(unaff_retaddr);
    if (funk[iVar1].delete_fn != (_func___cdecl_void_void_ptr *)0x0) {
      (*funk[iVar1].delete_fn)(param_2);
    }
  }
  return;
}
