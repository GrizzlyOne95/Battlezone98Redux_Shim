/*
 * Entry: 0049f611
 * Name: Howitzer::~Howitzer
 * Namespace: Howitzer
 * Signature: void ~Howitzer(Howitzer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Howitzer::~Howitzer(Howitzer *this)

{
  *(undefined ***)this = &TurretTank::_vftable__for__Attachable__;
  *(undefined ***)&this->field_0x20 = &TurretTank::_vftable__for__DistributedObject__;
  HoverCraft::~HoverCraft((HoverCraft *)this);
  return;
}
