/*
 * Entry: 004b3497
 * Name: Tug::~Tug
 * Namespace: Tug
 * Signature: void ~Tug(Tug * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tug::~Tug(Tug *this)

{
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  SetCargo(this,(GameObject *)0x0);
  HoverCraft::~HoverCraft((HoverCraft *)this);
  return;
}
