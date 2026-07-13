/*
 * Entry: 00466f08
 * Name: TugEnemy::CreateObject
 * Namespace: TugEnemy
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl TugEnemy::CreateObject(void)

{
  TugEnemy *pTVar1;
  
  pTVar1 = operator_new(0x4c);
  if (pTVar1 != (TugEnemy *)0x0) {
    pTVar1 = TugEnemy(pTVar1);
    return (SObject *)pTVar1;
  }
  return (SObject *)0x0;
}
