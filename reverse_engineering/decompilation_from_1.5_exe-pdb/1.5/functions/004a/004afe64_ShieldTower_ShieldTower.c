/*
 * Entry: 004afe64
 * Name: ShieldTower::ShieldTower
 * Namespace: ShieldTower
 * Signature: ShieldTower * ShieldTower(ShieldTower * this, _OBJ76 * param_1, ShieldTowerClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ShieldTower * __thiscall
ShieldTower::ShieldTower(ShieldTower *this,_OBJ76 *param_1,ShieldTowerClass *param_2)

{
  Building::Building((Building *)this,param_1,(BuildingClass *)param_2);
  this->powerSource = 0;
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  return this;
}
