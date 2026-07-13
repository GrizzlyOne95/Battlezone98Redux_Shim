/*
 * Entry: 004449c6
 * Name: Misns4Mission::CreateObject
 * Namespace: Misns4Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misns4Mission::CreateObject(void)

{
  Misns4Mission *pMVar1;
  
  pMVar1 = operator_new(0xe8);
  if (pMVar1 != (Misns4Mission *)0x0) {
    pMVar1 = Misns4Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
