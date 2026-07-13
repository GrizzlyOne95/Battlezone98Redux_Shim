/*
 * Entry: 004ad18e
 * Name: RepairDepotClass::Build
 * Namespace: RepairDepotClass
 * Signature: GameObject * Build(RepairDepotClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall RepairDepotClass::Build(RepairDepotClass *this,_OBJ76 *param_1)

{
  RepairDepot *pRVar1;
  
  pRVar1 = GameObject::operator_new(0x238);
  if (pRVar1 == (RepairDepot *)0x0) {
    pRVar1 = (RepairDepot *)0x0;
  }
  else {
    pRVar1 = RepairDepot::RepairDepot(pRVar1,param_1,this);
  }
  return (GameObject *)pRVar1;
}
