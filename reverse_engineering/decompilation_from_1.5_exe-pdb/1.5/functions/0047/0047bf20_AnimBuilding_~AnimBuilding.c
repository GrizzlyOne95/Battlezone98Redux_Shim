/*
 * Entry: 0047bf20
 * Name: AnimBuilding::~AnimBuilding
 * Namespace: AnimBuilding
 * Signature: void ~AnimBuilding(AnimBuilding * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AnimBuilding::~AnimBuilding(AnimBuilding *this)

{
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  Building::~Building((Building *)this);
  return;
}
