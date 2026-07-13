/*
 * Entry: 004b180c
 * Name: SupplyDepot::SupplyDepot
 * Namespace: SupplyDepot
 * Signature: SupplyDepot * SupplyDepot(SupplyDepot * this, _OBJ76 * param_1, SupplyDepotClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SupplyDepot * __thiscall
SupplyDepot::SupplyDepot(SupplyDepot *this,_OBJ76 *param_1,SupplyDepotClass *param_2)

{
  Building::Building((Building *)this,param_1,(BuildingClass *)param_2);
  this->supplyTimer = 0.0;
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  AnimObj_Start(param_1,0,&this->animHandle);
  return this;
}
