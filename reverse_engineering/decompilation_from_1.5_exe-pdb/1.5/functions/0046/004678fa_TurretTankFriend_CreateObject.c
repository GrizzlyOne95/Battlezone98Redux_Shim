/*
 * Entry: 004678fa
 * Name: TurretTankFriend::CreateObject
 * Namespace: TurretTankFriend
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl TurretTankFriend::CreateObject(void)

{
  TurretTankFriend *pTVar1;
  
  pTVar1 = operator_new(0x88);
  if (pTVar1 != (TurretTankFriend *)0x0) {
    pTVar1 = TurretTankFriend(pTVar1);
    return (SObject *)pTVar1;
  }
  return (SObject *)0x0;
}
