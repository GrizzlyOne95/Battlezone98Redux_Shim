/*
 * Entry: 00456a27
 * Name: PathSpawn::CreateObject
 * Namespace: PathSpawn
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl PathSpawn::CreateObject(void)

{
  PathSpawn *pPVar1;
  
  pPVar1 = operator_new(0x114c);
  if (pPVar1 != (PathSpawn *)0x0) {
    pPVar1 = PathSpawn(pPVar1);
    return (SObject *)pPVar1;
  }
  return (SObject *)0x0;
}
