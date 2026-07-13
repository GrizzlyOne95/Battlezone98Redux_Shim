/*
 * Entry: 0047db4a
 * Name: APC::~APC
 * Namespace: APC
 * Signature: void ~APC(APC * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall APC::~APC(APC *this)

{
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  HoverCraft::~HoverCraft((HoverCraft *)this);
  return;
}
