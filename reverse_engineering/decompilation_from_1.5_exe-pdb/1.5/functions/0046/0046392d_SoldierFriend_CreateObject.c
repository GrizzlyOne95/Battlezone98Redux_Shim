/*
 * Entry: 0046392d
 * Name: SoldierFriend::CreateObject
 * Namespace: SoldierFriend
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl SoldierFriend::CreateObject(void)

{
  SoldierFriend *pSVar1;
  
  pSVar1 = operator_new(0x78);
  if (pSVar1 != (SoldierFriend *)0x0) {
    pSVar1 = SoldierFriend(pSVar1);
    return (SObject *)pSVar1;
  }
  return (SObject *)0x0;
}
