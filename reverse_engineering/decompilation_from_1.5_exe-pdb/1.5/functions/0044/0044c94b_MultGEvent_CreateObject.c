/*
 * Entry: 0044c94b
 * Name: MultGEvent::CreateObject
 * Namespace: MultGEvent
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl MultGEvent::CreateObject(void)

{
  MultGEvent *pMVar1;
  
  pMVar1 = operator_new(0x40c);
  if (pMVar1 != (MultGEvent *)0x0) {
    pMVar1 = MultGEvent(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
