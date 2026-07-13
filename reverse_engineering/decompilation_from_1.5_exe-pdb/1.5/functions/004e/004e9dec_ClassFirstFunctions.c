/*
 * Entry: 004e9dec
 * Name: ClassFirstFunctions
 * Namespace: Global
 * Signature: void ClassFirstFunctions(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ClassFirstFunctions(void)

{
  wrap_struct *pwVar1;
  wrap_struct *pwVar2;
  wrap_struct *unaff_ESI;
  
  pwVar2 = InitList;
  while (pwVar2 != (wrap_struct *)0x0) {
    pwVar1 = pwVar2->next;
    DeleteWrapper(&InitList,pwVar2);
    nInitList = nInitList + -1;
    ClassCallFirst(unaff_ESI);
    pwVar2 = pwVar1;
  }
  return;
}
