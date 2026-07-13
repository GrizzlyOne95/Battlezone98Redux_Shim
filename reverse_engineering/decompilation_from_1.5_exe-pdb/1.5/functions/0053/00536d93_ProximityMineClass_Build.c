/*
 * Entry: 00536d93
 * Name: ProximityMineClass::Build
 * Namespace: ProximityMineClass
 * Signature: GameObject * Build(ProximityMineClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall ProximityMineClass::Build(ProximityMineClass *this,_OBJ76 *param_1)

{
  ProximityMine *pPVar1;
  
  pPVar1 = GameObject::operator_new(0x240);
  if (pPVar1 == (ProximityMine *)0x0) {
    pPVar1 = (ProximityMine *)0x0;
  }
  else {
    pPVar1 = ProximityMine::ProximityMine(pPVar1,param_1,this);
  }
  return (GameObject *)pPVar1;
}
