/*
 * Entry: 0040dc9e
 * Name: ArtilleryFriend::CreateObject
 * Namespace: ArtilleryFriend
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl ArtilleryFriend::CreateObject(void)

{
  ArtilleryFriend *pAVar1;
  
  pAVar1 = operator_new(0x7c);
  if (pAVar1 != (ArtilleryFriend *)0x0) {
    pAVar1 = ArtilleryFriend(pAVar1);
    return (SObject *)pAVar1;
  }
  return (SObject *)0x0;
}
