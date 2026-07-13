/*
 * Entry: 004b6bb4
 * Name: Walker::~Walker
 * Namespace: Walker
 * Signature: void ~Walker(Walker * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Walker::~Walker(Walker *this)

{
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  Craft::~Craft((Craft *)this);
  return;
}
