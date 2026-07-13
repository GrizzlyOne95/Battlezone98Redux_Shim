/*
 * Entry: 00411929
 * Name: MUFEnemy::CreateObject
 * Namespace: MUFEnemy
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl MUFEnemy::CreateObject(void)

{
  MUFEnemy *pMVar1;
  
  pMVar1 = operator_new(0x40);
  if (pMVar1 != (MUFEnemy *)0x0) {
    pMVar1 = MUFEnemy(pMVar1);
    return (SObject *)pMVar1;
  }
  return (SObject *)0x0;
}
