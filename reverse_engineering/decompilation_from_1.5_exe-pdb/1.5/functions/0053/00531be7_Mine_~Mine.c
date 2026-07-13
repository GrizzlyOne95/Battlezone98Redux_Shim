/*
 * Entry: 00531be7
 * Name: Mine::~Mine
 * Namespace: Mine
 * Signature: void ~Mine(Mine * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Mine::~Mine(Mine *this)

{
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  Building::~Building((Building *)this);
  return;
}
