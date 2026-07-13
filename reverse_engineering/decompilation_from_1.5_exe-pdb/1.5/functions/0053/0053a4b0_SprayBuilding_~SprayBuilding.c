/*
 * Entry: 0053a4b0
 * Name: SprayBuilding::~SprayBuilding
 * Namespace: SprayBuilding
 * Signature: void ~SprayBuilding(SprayBuilding * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SprayBuilding::~SprayBuilding(SprayBuilding *this)

{
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  Building::~Building((Building *)this);
  return;
}
