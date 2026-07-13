/*
 * Entry: 0049c2bd
 * Name: HealthPowerupClass::Build
 * Namespace: HealthPowerupClass
 * Signature: GameObject * Build(HealthPowerupClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall HealthPowerupClass::Build(HealthPowerupClass *this,_OBJ76 *param_1)

{
  HealthPowerup *pHVar1;
  
  pHVar1 = GameObject::operator_new(0x228);
  if (pHVar1 == (HealthPowerup *)0x0) {
    pHVar1 = (HealthPowerup *)0x0;
  }
  else {
    pHVar1 = HealthPowerup::HealthPowerup(pHVar1,param_1,this);
  }
  return (GameObject *)pHVar1;
}
