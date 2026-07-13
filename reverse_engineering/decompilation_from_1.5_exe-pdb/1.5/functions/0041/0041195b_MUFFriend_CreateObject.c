/*
 * Entry: 0041195b
 * Name: MUFFriend::CreateObject
 * Namespace: MUFFriend
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl MUFFriend::CreateObject(void)

{
  MUFFriend *pMVar1;
  
  pMVar1 = operator_new(0x40);
  if (pMVar1 != (MUFFriend *)0x0) {
    pMVar1 = MUFFriend(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
