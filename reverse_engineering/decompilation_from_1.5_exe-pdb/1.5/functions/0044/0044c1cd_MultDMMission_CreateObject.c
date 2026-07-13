/*
 * Entry: 0044c1cd
 * Name: MultDMMission::CreateObject
 * Namespace: MultDMMission
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl MultDMMission::CreateObject(void)

{
  MultDMMission *pMVar1;
  
  pMVar1 = operator_new(0x70);
  if (pMVar1 != (MultDMMission *)0x0) {
    pMVar1 = MultDMMission(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
