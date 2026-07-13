/*
 * Entry: 0047bf65
 * Name: AnimBuildingClass::Build
 * Namespace: AnimBuildingClass
 * Signature: GameObject * Build(AnimBuildingClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall AnimBuildingClass::Build(AnimBuildingClass *this,_OBJ76 *param_1)

{
  AnimBuilding *pAVar1;
  
  pAVar1 = GameObject::operator_new(0x238);
  if (pAVar1 == (AnimBuilding *)0x0) {
    pAVar1 = (AnimBuilding *)0x0;
  }
  else {
    pAVar1 = AnimBuilding::AnimBuilding(pAVar1,param_1,this);
  }
  return (GameObject *)pAVar1;
}
