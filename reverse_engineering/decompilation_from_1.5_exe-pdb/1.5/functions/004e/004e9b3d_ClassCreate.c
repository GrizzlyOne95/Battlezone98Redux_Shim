/*
 * Entry: 004e9b3d
 * Name: ClassCreate
 * Namespace: Global
 * Signature: void ClassCreate(_OBJ76 * param_1, OBJECT_CLASS_T param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ClassCreate(_OBJ76 *param_1,OBJECT_CLASS_T param_2)

{
  int iVar1;
  void *pvVar2;
  OBJECT_CLASS_T unaff_ESI;
  
  param_1->class_id = param_2;
  iVar1 = ClassIDtoIndex(unaff_ESI);
  if (0 < iVar1) {
    if (funk[iVar1].new_fn != (_func___cdecl_void_ptr *)0x0) {
      pvVar2 = (*funk[iVar1].new_fn)();
      param_1->class_ptr = pvVar2;
    }
    i_got_dibs_on_obj(param_1,".\\Obj76\\Classfnc.c");
    ObjList = NewWrapper(ObjList,(wrap_struct *)0x0,param_1);
    InitList = NewWrapper(InitList,(wrap_struct *)0x0,ObjList);
    nInitList = nInitList + 1;
    nObjList = nObjList + 1;
  }
  return;
}
