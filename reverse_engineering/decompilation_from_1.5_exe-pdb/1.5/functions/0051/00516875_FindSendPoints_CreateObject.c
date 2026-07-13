/*
 * Entry: 00516875
 * Name: FindSendPoints::CreateObject
 * Namespace: FindSendPoints
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl FindSendPoints::CreateObject(void)

{
  FindSendPoints *pFVar1;
  
  pFVar1 = operator_new(0x20);
  if (pFVar1 != (FindSendPoints *)0x0) {
    pFVar1 = FindSendPoints(pFVar1);
    return (SObject *)pFVar1;
  }
  return (SObject *)0x0;
}
