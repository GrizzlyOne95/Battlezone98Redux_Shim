/*
 * Entry: 00445d3e
 * Name: Misns6Mission::CreateObject
 * Namespace: Misns6Mission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl Misns6Mission::CreateObject(void)

{
  Misns6Mission *pMVar1;
  
  pMVar1 = operator_new(0xbc);
  if (pMVar1 != (Misns6Mission *)0x0) {
    pMVar1 = Misns6Mission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
