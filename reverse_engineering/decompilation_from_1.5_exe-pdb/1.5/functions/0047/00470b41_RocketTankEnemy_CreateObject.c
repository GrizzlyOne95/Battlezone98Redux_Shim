/*
 * Entry: 00470b41
 * Name: RocketTankEnemy::CreateObject
 * Namespace: RocketTankEnemy
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl RocketTankEnemy::CreateObject(void)

{
  RocketTankEnemy *pRVar1;
  
  pRVar1 = operator_new(0x78);
  if (pRVar1 != (RocketTankEnemy *)0x0) {
    pRVar1 = RocketTankEnemy(pRVar1);
    return (SObject *)pRVar1;
  }
  return (SObject *)0x0;
}
