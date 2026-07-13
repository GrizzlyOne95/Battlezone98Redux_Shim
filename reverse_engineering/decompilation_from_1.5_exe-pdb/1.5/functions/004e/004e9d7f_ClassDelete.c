/*
 * Entry: 004e9d7f
 * Name: ClassDelete
 * Namespace: Global
 * Signature: void ClassDelete(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ClassDelete(_OBJ76 *param_1)

{
  _OBJ76 *p_Var1;
  wrap_struct *pwVar2;
  wrap_struct *unaff_EDI;
  
  p_Var1 = validate_obj(param_1,".\\Obj76\\Classfnc.c");
  pwVar2 = ObjList;
  if (p_Var1 != (_OBJ76 *)0x0) {
    ZapClass(p_Var1->class_id,p_Var1->class_ptr);
    p_Var1->class_id = CLASS_ID_NONE;
    p_Var1->class_ptr = (void *)0x0;
    pwVar2 = ObjList;
  }
  while( true ) {
    if (pwVar2 == (wrap_struct *)0x0) {
      return;
    }
    if (pwVar2->ptr == param_1) break;
    pwVar2 = pwVar2->next;
  }
  if (p_Var1 != (_OBJ76 *)0x0) {
    release_obj(p_Var1,".\\Obj76\\Classfnc.c");
  }
  DeleteFromObjlist(unaff_EDI);
  return;
}
