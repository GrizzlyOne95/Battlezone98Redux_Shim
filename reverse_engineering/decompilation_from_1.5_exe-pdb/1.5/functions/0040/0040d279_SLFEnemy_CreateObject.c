/*
 * Entry: 0040d279
 * Name: SLFEnemy::CreateObject
 * Namespace: SLFEnemy
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl SLFEnemy::CreateObject(void)

{
  SLFEnemy *pSVar1;
  
  pSVar1 = operator_new(0x48);
  if (pSVar1 != (SLFEnemy *)0x0) {
    pSVar1 = SLFEnemy(pSVar1);
    return (SObject *)pSVar1;
  }
  return (SObject *)0x0;
}
