/*
 * Entry: 004afe8e
 * Name: ShieldTower::~ShieldTower
 * Namespace: ShieldTower
 * Signature: void ~ShieldTower(ShieldTower * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ShieldTower::~ShieldTower(ShieldTower *this)

{
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  Building::~Building((Building *)this);
  return;
}
