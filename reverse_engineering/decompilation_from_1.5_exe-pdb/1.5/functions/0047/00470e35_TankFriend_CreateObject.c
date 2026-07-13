/*
 * Entry: 00470e35
 * Name: TankFriend::CreateObject
 * Namespace: TankFriend
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl TankFriend::CreateObject(void)

{
  TankFriend *pTVar1;
  
  pTVar1 = operator_new(0x78);
  if (pTVar1 != (TankFriend *)0x0) {
    pTVar1 = TankFriend(pTVar1);
    return (SObject *)pTVar1;
  }
  return (SObject *)0x0;
}
