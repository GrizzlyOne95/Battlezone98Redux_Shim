/*
 * Entry: 004e990d
 * Name: DeleteClassHandler
 * Namespace: Global
 * Signature: void DeleteClassHandler(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DeleteClassHandler(void)

{
  _OBJ76 *p_Var1;
  
  while (InitList != (wrap_struct *)0x0) {
    DeleteWrapper(&InitList,InitList);
    nInitList = nInitList + -1;
  }
  InitList = (wrap_struct *)0x0;
  while (ObjList != (wrap_struct *)0x0) {
    p_Var1 = validate_obj(ObjList->ptr,".\\Obj76\\Classfnc.c");
    if (p_Var1 != (_OBJ76 *)0x0) {
      release_obj(p_Var1,".\\Obj76\\Classfnc.c");
    }
    DeleteWrapper(&ObjList,ObjList);
    nObjList = nObjList + -1;
  }
  return;
}
