/*
 * Entry: 004835ce
 * Name: BuildingClass::Build
 * Namespace: BuildingClass
 * Signature: GameObject * Build(BuildingClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall BuildingClass::Build(BuildingClass *this,_OBJ76 *param_1)

{
  Building *pBVar1;
  
  pBVar1 = GameObject::operator_new(0x230);
  if (pBVar1 == (Building *)0x0) {
    pBVar1 = (Building *)0x0;
  }
  else {
    pBVar1 = Building::Building(pBVar1,param_1,this);
  }
  return (GameObject *)pBVar1;
}
