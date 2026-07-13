/*
 * Entry: 004e9ab1
 * Name: DeleteFromObjlist
 * Namespace: Global
 * Signature: void DeleteFromObjlist(wrap_struct * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DeleteFromObjlist(wrap_struct *param_1)

{
  wrap_struct *pwVar1;
  wrap_struct *unaff_ESI;
  
  pwVar1 = InitList;
  do {
    if (pwVar1 == (wrap_struct *)0x0) {
LAB_004e9ad8:
      DeleteWrapper(&ObjList,unaff_ESI);
      nInitList = nInitList + -1;
      return;
    }
    if (pwVar1->ptr == unaff_ESI) {
      DeleteWrapper(&InitList,pwVar1);
      nInitList = nInitList + -1;
      goto LAB_004e9ad8;
    }
    pwVar1 = pwVar1->next;
  } while( true );
}
