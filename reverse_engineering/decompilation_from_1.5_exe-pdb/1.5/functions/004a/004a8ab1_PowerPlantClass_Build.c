/*
 * Entry: 004a8ab1
 * Name: PowerPlantClass::Build
 * Namespace: PowerPlantClass
 * Signature: GameObject * Build(PowerPlantClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall PowerPlantClass::Build(PowerPlantClass *this,_OBJ76 *param_1)

{
  PowerPlant *pPVar1;
  
  pPVar1 = GameObject::operator_new(0x238);
  if (pPVar1 == (PowerPlant *)0x0) {
    pPVar1 = (PowerPlant *)0x0;
  }
  else {
    pPVar1 = PowerPlant::PowerPlant(pPVar1,param_1,this);
  }
  return (GameObject *)pPVar1;
}
