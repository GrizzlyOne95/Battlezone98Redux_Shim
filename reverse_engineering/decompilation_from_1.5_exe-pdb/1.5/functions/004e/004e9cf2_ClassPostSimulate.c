/*
 * Entry: 004e9cf2
 * Name: ClassPostSimulate
 * Namespace: Global
 * Signature: void ClassPostSimulate(wrap_struct * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ClassPostSimulate(wrap_struct *param_1)

{
  int in_EAX;
  _OBJ76 *p_Var1;
  int iVar2;
  wrap_struct *unaff_EDI;
  
  p_Var1 = validate_obj(*(_OBJ76 **)(in_EAX + 8),".\\Obj76\\Classfnc.c");
  if (p_Var1 == (_OBJ76 *)0x0) {
    DeleteFromObjlist(unaff_EDI);
  }
  else {
    iVar2 = ClassIDtoIndex((OBJECT_CLASS_T)unaff_EDI);
    if (funk[iVar2].post_simulate_fn != (_func___cdecl_void__OBJ76_ptr *)0x0) {
      (*funk[iVar2].post_simulate_fn)(p_Var1);
    }
  }
  return;
}
