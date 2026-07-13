/*
 * Entry: 00414f87
 * Name: GunTowerEnemy::CreateObject
 * Namespace: GunTowerEnemy
 * Signature: SObject * CreateObject(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SObject * __cdecl GunTowerEnemy::CreateObject(void)

{
  GunTowerEnemy *pGVar1;
  
  pGVar1 = operator_new(0x58);
  if (pGVar1 != (GunTowerEnemy *)0x0) {
    pGVar1 = GunTowerEnemy(pGVar1);
    return (SObject *)pGVar1;
  }
  return (SObject *)0x0;
}
