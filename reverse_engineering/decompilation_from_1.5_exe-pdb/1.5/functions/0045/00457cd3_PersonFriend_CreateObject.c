/*
 * Entry: 00457cd3
 * Name: PersonFriend::CreateObject
 * Namespace: PersonFriend
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl PersonFriend::CreateObject(void)

{
  PersonFriend *pPVar1;
  
  pPVar1 = operator_new(0x80);
  if (pPVar1 != (PersonFriend *)0x0) {
    pPVar1 = PersonFriend(pPVar1);
    return (SObject *)pPVar1;
  }
  return (SObject *)0x0;
}
