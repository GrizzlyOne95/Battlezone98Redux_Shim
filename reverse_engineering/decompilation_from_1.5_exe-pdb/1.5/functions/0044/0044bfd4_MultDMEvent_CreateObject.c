/*
 * Entry: 0044bfd4
 * Name: MultDMEvent::CreateObject
 * Namespace: MultDMEvent
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl MultDMEvent::CreateObject(void)

{
  MultDMEvent *pMVar1;
  
  pMVar1 = operator_new(0x38);
  if (pMVar1 != (MultDMEvent *)0x0) {
    pMVar1 = MultDMEvent(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
