/*
 * Entry: 0044d788
 * Name: NetProcess::CreateObject
 * Namespace: NetProcess
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl NetProcess::CreateObject(void)

{
  NetProcess *pNVar1;
  
  pNVar1 = operator_new(0x14);
  if (pNVar1 != (NetProcess *)0x0) {
    pNVar1 = NetProcess(pNVar1);
    return (SObject *)pNVar1;
  }
  return (SObject *)0x0;
}
