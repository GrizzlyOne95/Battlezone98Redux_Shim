/*
 * Entry: 004aa3c4
 * Name: PowerUpClass::Build
 * Namespace: PowerUpClass
 * Signature: GameObject * Build(PowerUpClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall PowerUpClass::Build(PowerUpClass *this,_OBJ76 *param_1)

{
  PowerUp *pPVar1;
  
  pPVar1 = GameObject::operator_new(0x228);
  if (pPVar1 == (PowerUp *)0x0) {
    pPVar1 = (PowerUp *)0x0;
  }
  else {
    pPVar1 = PowerUp::PowerUp(pPVar1,param_1,this);
  }
  return (GameObject *)pPVar1;
}
