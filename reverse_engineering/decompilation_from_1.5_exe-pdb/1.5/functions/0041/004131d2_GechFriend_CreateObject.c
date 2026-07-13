/*
 * Entry: 004131d2
 * Name: GechFriend::CreateObject
 * Namespace: GechFriend
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl GechFriend::CreateObject(void)

{
  GechFriend *pGVar1;
  
  pGVar1 = operator_new(0x78);
  if (pGVar1 != (GechFriend *)0x0) {
    pGVar1 = GechFriend(pGVar1);
    return (SObject *)pGVar1;
  }
  return (SObject *)0x0;
}
