/*
 * Entry: 0040c200
 * Name: APCFriend::CreateObject
 * Namespace: APCFriend
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl APCFriend::CreateObject(void)

{
  APCFriend *pAVar1;
  
  pAVar1 = operator_new(0x58);
  if (pAVar1 != (APCFriend *)0x0) {
    pAVar1 = APCFriend(pAVar1);
    return (SObject *)pAVar1;
  }
  return (SObject *)0x0;
}
