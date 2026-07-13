/*
 * Entry: 00410b04
 * Name: RigFriend::CreateObject
 * Namespace: RigFriend
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl RigFriend::CreateObject(void)

{
  RigFriend *pRVar1;
  
  pRVar1 = operator_new(0x58);
  if (pRVar1 != (RigFriend *)0x0) {
    pRVar1 = RigFriend(pRVar1);
    return (SObject *)pRVar1;
  }
  return (SObject *)0x0;
}
