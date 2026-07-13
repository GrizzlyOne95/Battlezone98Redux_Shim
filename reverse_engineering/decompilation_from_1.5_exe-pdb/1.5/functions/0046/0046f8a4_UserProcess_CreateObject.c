/*
 * Entry: 0046f8a4
 * Name: UserProcess::CreateObject
 * Namespace: UserProcess
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl UserProcess::CreateObject(void)

{
  UserProcess *pUVar1;
  
  pUVar1 = operator_new(0x70);
  if (pUVar1 != (UserProcess *)0x0) {
    pUVar1 = UserProcess(pUVar1);
    return (SObject *)pUVar1;
  }
  return (SObject *)0x0;
}
