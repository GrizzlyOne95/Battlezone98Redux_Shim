/*
 * Entry: 0053a737
 * Name: SprayBuildingClass::Build
 * Namespace: SprayBuildingClass
 * Signature: GameObject * Build(SprayBuildingClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall SprayBuildingClass::Build(SprayBuildingClass *this,_OBJ76 *param_1)

{
  SprayBuilding *pSVar1;
  
  pSVar1 = GameObject::operator_new(0x240);
  if (pSVar1 == (SprayBuilding *)0x0) {
    pSVar1 = (SprayBuilding *)0x0;
  }
  else {
    pSVar1 = SprayBuilding::SprayBuilding(pSVar1,param_1,this);
  }
  return (GameObject *)pSVar1;
}
