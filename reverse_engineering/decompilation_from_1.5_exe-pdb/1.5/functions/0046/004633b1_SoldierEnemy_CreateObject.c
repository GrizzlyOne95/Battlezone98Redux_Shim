/*
 * Entry: 004633b1
 * Name: SoldierEnemy::CreateObject
 * Namespace: SoldierEnemy
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl SoldierEnemy::CreateObject(void)

{
  SoldierEnemy *pSVar1;
  
  pSVar1 = operator_new(0x78);
  if (pSVar1 != (SoldierEnemy *)0x0) {
    pSVar1 = SoldierEnemy(pSVar1);
    return (SObject *)pSVar1;
  }
  return (SObject *)0x0;
}
