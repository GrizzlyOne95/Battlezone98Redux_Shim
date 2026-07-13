/*
 * Entry: 0052d024
 * Name: DayWrecker::~DayWrecker
 * Namespace: DayWrecker
 * Signature: void ~DayWrecker(DayWrecker * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DayWrecker::~DayWrecker(DayWrecker *this)

{
  *(undefined ***)this = &PowerUp::_vftable__for__Attachable__;
  *(undefined ***)&this->field_0x20 = &PowerUp::_vftable__for__DistributedObject__;
  GameObject::~GameObject((GameObject *)this);
  return;
}
