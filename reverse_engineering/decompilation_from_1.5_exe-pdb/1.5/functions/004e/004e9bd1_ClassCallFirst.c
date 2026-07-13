/*
 * Entry: 004e9bd1
 * Name: ClassCallFirst
 * Namespace: Global
 * Signature: void ClassCallFirst(wrap_struct * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ClassCallFirst(wrap_struct *param_1)

{
  _OBJ76 *p_Var1;
  int iVar2;
  wrap_struct *unaff_EBX;
  OBJECT_CLASS_T unaff_ESI;
  
  p_Var1 = validate_obj(unaff_EBX->ptr,".\\Obj76\\Classfnc.c");
  if (p_Var1 == (_OBJ76 *)0x0) {
    DeleteWrapper(&ObjList,unaff_EBX);
    nObjList = nObjList + -1;
  }
  else {
    iVar2 = ClassIDtoIndex(unaff_ESI);
    if (funk[iVar2].first_fn != (_func___cdecl_void__OBJ76_ptr *)0x0) {
      (*funk[iVar2].first_fn)(p_Var1);
    }
    if ((funk[iVar2].simulate_fn == (_func___cdecl_void__OBJ76_ptr *)0x0) &&
       (funk[iVar2].post_simulate_fn == (_func___cdecl_void__OBJ76_ptr *)0x0)) {
      release_obj(unaff_EBX->ptr,".\\Obj76\\Classfnc.c");
      DeleteWrapper(&ObjList,unaff_EBX);
      nObjList = nObjList + -1;
    }
  }
  return;
}
