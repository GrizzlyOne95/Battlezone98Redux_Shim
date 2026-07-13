/*
 * Entry: 00459993
 * Name: RecyclerFriend::CreateObject
 * Namespace: RecyclerFriend
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl RecyclerFriend::CreateObject(void)

{
  RecyclerFriend *pRVar1;
  
  pRVar1 = operator_new(0x58);
  if (pRVar1 != (RecyclerFriend *)0x0) {
    pRVar1 = RecyclerFriend(pRVar1);
    return (SObject *)pRVar1;
  }
  return (SObject *)0x0;
}
