/*
 * Entry: 004ad367
 * Name: SAV::~SAV
 * Namespace: SAV
 * Signature: void ~SAV(SAV * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SAV::~SAV(SAV *this)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)this->_padding_;
  this->_padding_ = (int)&HoverCraft::_vftable__for__Attachable__;
  this->_padding_ = (int)&HoverCraft::_vftable__for__DistributedObject__;
  if (puVar1 != (undefined4 *)0x0) {
    (**(code **)*puVar1)(1);
    this->_padding_ = 0;
  }
  Craft::~Craft((Craft *)this);
  return;
}
