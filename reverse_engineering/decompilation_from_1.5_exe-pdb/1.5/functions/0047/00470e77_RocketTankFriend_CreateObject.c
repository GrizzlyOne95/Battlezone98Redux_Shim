/*
 * Entry: 00470e77
 * Name: RocketTankFriend::CreateObject
 * Namespace: RocketTankFriend
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl RocketTankFriend::CreateObject(void)

{
  RocketTankFriend *pRVar1;
  
  pRVar1 = operator_new(0x78);
  if (pRVar1 != (RocketTankFriend *)0x0) {
    pRVar1 = RocketTankFriend(pRVar1);
    return (SObject *)pRVar1;
  }
  return (SObject *)0x0;
}
