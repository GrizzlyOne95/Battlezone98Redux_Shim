/*
 * Entry: 004e997a
 * Name: ClassNoFirstFunctions
 * Namespace: Global
 * Signature: void ClassNoFirstFunctions(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ClassNoFirstFunctions(void)

{
  wrap_struct *pwVar1;
  wrap_struct *pwVar2;
  
  pwVar2 = InitList;
  while (pwVar2 != (wrap_struct *)0x0) {
    pwVar1 = pwVar2->next;
    DeleteWrapper(&InitList,pwVar2);
    nInitList = nInitList + -1;
    pwVar2 = pwVar1;
  }
  return;
}
