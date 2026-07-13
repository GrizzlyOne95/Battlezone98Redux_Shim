/*
 * Entry: 004acf42
 * Name: RepairDepot::RepairDepot
 * Namespace: RepairDepot
 * Signature: RepairDepot * RepairDepot(RepairDepot * this, _OBJ76 * param_1, RepairDepotClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RepairDepot * __thiscall
RepairDepot::RepairDepot(RepairDepot *this,_OBJ76 *param_1,RepairDepotClass *param_2)

{
  Building::Building((Building *)this,param_1,(BuildingClass *)param_2);
  this->repairTimer = 0.0;
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  AnimObj_Start(param_1,0,&this->animHandle);
  return this;
}
