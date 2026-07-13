/*
 * Entry: 004b1a58
 * Name: SupplyDepotClass::Build
 * Namespace: SupplyDepotClass
 * Signature: GameObject * Build(SupplyDepotClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall SupplyDepotClass::Build(SupplyDepotClass *this,_OBJ76 *param_1)

{
  SupplyDepot *pSVar1;
  
  pSVar1 = GameObject::operator_new(0x238);
  if (pSVar1 == (SupplyDepot *)0x0) {
    pSVar1 = (SupplyDepot *)0x0;
  }
  else {
    pSVar1 = SupplyDepot::SupplyDepot(pSVar1,param_1,this);
  }
  return (GameObject *)pSVar1;
}
