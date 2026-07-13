/*
 * Entry: 00470e4b
 * Name: ScoutFriend::CreateObject
 * Namespace: ScoutFriend
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl ScoutFriend::CreateObject(void)

{
  ScoutFriend *pSVar1;
  
  pSVar1 = operator_new(0x78);
  if (pSVar1 != (ScoutFriend *)0x0) {
    pSVar1 = ScoutFriend(pSVar1);
    return (SObject *)pSVar1;
  }
  return (SObject *)0x0;
}
