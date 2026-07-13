/*
 * Entry: 0040dcd0
 * Name: ArtilleryEnemy::CreateObject
 * Namespace: ArtilleryEnemy
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl ArtilleryEnemy::CreateObject(void)

{
  ArtilleryEnemy *pAVar1;
  
  pAVar1 = operator_new(0x7c);
  if (pAVar1 != (ArtilleryEnemy *)0x0) {
    pAVar1 = ArtilleryEnemy(pAVar1);
    return (SObject *)pAVar1;
  }
  return (SObject *)0x0;
}
