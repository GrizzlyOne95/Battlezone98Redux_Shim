/*
 * Entry: 004e9e1d
 * Name: ClassSimulateAll
 * Namespace: Global
 * Signature: void ClassSimulateAll(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ClassSimulateAll(void)

{
  wrap_struct *pwVar1;
  wrap_struct *pwVar2;
  _OBJ76 *p_Var3;
  int iVar4;
  wrap_struct *unaff_EDI;
  
  pwVar2 = ObjList;
  while (pwVar2 != (wrap_struct *)0x0) {
    pwVar1 = pwVar2->next;
    p_Var3 = validate_obj(pwVar2->ptr,".\\Obj76\\Classfnc.c");
    pwVar2 = pwVar1;
    if (p_Var3 == (_OBJ76 *)0x0) {
      DeleteFromObjlist(unaff_EDI);
    }
    else {
      iVar4 = ClassIDtoIndex((OBJECT_CLASS_T)unaff_EDI);
      if (funk[iVar4].simulate_fn != (_func___cdecl_void__OBJ76_ptr *)0x0) {
        (*funk[iVar4].simulate_fn)(p_Var3);
      }
    }
  }
  return;
}
