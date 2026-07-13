/*
 * Entry: 00470e61
 * Name: BomberFriend::CreateObject
 * Namespace: BomberFriend
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl BomberFriend::CreateObject(void)

{
  BomberFriend *pBVar1;
  
  pBVar1 = operator_new(0x78);
  if (pBVar1 != (BomberFriend *)0x0) {
    pBVar1 = BomberFriend(pBVar1);
    return (SObject *)pBVar1;
  }
  return (SObject *)0x0;
}
