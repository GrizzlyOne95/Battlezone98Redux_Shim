/*
 * Entry: 0046792f
 * Name: TurretTankEnemy::CreateObject
 * Namespace: TurretTankEnemy
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl TurretTankEnemy::CreateObject(void)

{
  TurretTankEnemy *pTVar1;
  
  pTVar1 = operator_new(0x88);
  if (pTVar1 != (TurretTankEnemy *)0x0) {
    pTVar1 = TurretTankEnemy(pTVar1);
    return (SObject *)pTVar1;
  }
  return (SObject *)0x0;
}
