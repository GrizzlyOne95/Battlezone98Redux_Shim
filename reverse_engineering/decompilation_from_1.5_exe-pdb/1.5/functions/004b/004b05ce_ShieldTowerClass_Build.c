/*
 * Entry: 004b05ce
 * Name: ShieldTowerClass::Build
 * Namespace: ShieldTowerClass
 * Signature: GameObject * Build(ShieldTowerClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall ShieldTowerClass::Build(ShieldTowerClass *this,_OBJ76 *param_1)

{
  ShieldTower *pSVar1;
  
  pSVar1 = GameObject::operator_new(0x238);
  if (pSVar1 == (ShieldTower *)0x0) {
    pSVar1 = (ShieldTower *)0x0;
  }
  else {
    pSVar1 = ShieldTower::ShieldTower(pSVar1,param_1,this);
  }
  return (GameObject *)pSVar1;
}
