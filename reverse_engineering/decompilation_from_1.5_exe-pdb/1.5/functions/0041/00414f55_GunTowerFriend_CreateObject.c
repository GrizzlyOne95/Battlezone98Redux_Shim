/*
 * Entry: 00414f55
 * Name: GunTowerFriend::CreateObject
 * Namespace: GunTowerFriend
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl GunTowerFriend::CreateObject(void)

{
  GunTowerFriend *pGVar1;
  
  pGVar1 = operator_new(0x58);
  if (pGVar1 != (GunTowerFriend *)0x0) {
    pGVar1 = GunTowerFriend(pGVar1);
    return (SObject *)pGVar1;
  }
  return (SObject *)0x0;
}
