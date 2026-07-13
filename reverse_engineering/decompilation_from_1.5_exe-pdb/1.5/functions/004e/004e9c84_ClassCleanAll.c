/*
 * Entry: 004e9c84
 * Name: ClassCleanAll
 * Namespace: Global
 * Signature: void ClassCleanAll(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ClassCleanAll(void)

{
  wrap_struct *pwVar1;
  wrap_struct *pwVar2;
  _OBJ76 *p_Var3;
  wrap_struct *unaff_EDI;
  
  pwVar2 = ObjList;
  while (pwVar2 != (wrap_struct *)0x0) {
    pwVar1 = pwVar2->next;
    p_Var3 = validate_obj(pwVar2->ptr,".\\Obj76\\Classfnc.c");
    pwVar2 = pwVar1;
    if (p_Var3 == (_OBJ76 *)0x0) {
      DeleteFromObjlist(unaff_EDI);
    }
  }
  return;
}
