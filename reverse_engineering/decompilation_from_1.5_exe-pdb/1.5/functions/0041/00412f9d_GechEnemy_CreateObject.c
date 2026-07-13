/*
 * Entry: 00412f9d
 * Name: GechEnemy::CreateObject
 * Namespace: GechEnemy
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl GechEnemy::CreateObject(void)

{
  GechEnemy *pGVar1;
  
  pGVar1 = operator_new(0x78);
  if (pGVar1 != (GechEnemy *)0x0) {
    pGVar1 = GechEnemy(pGVar1);
    return (SObject *)pGVar1;
  }
  return (SObject *)0x0;
}
