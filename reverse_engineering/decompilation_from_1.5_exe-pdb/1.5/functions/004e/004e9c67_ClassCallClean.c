/*
 * Entry: 004e9c67
 * Name: ClassCallClean
 * Namespace: Global
 * Signature: void ClassCallClean(wrap_struct * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ClassCallClean(wrap_struct *param_1)

{
  int in_EAX;
  _OBJ76 *p_Var1;
  wrap_struct *unaff_ESI;
  
  p_Var1 = validate_obj(*(_OBJ76 **)(in_EAX + 8),".\\Obj76\\Classfnc.c");
  if (p_Var1 == (_OBJ76 *)0x0) {
    DeleteFromObjlist(unaff_ESI);
  }
  return;
}
