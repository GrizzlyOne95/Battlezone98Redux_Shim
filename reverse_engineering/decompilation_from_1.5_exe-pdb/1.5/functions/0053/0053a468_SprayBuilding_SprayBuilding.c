/*
 * Entry: 0053a468
 * Name: SprayBuilding::SprayBuilding
 * Namespace: SprayBuilding
 * Signature: SprayBuilding * SprayBuilding(SprayBuilding * this, _OBJ76 * param_1, SprayBuildingClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SprayBuilding * __thiscall
SprayBuilding::SprayBuilding(SprayBuilding *this,_OBJ76 *param_1,SprayBuildingClass *param_2)

{
  Building::Building((Building *)this,param_1,(BuildingClass *)param_2);
  this->go = (_gas_object *)0x0;
  this->dmg_player = false;
  this->dmg_remote = false;
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  this->shotTimer = -param_2->triggerDelay;
  return this;
}
