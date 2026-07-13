/*
 * Entry: 004639cb
 * Name: TorpedoProcess::CreateObject
 * Namespace: TorpedoProcess
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl TorpedoProcess::CreateObject(void)

{
  TorpedoProcess *pTVar1;
  
  pTVar1 = operator_new(0x14);
  if (pTVar1 != (TorpedoProcess *)0x0) {
    pTVar1 = TorpedoProcess(pTVar1);
    return (SObject *)pTVar1;
  }
  return (SObject *)0x0;
}
