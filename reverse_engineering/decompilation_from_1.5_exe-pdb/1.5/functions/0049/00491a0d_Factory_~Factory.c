/*
 * Entry: 00491a0d
 * Name: Factory::~Factory
 * Namespace: Factory
 * Signature: void ~Factory(Factory * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Factory::~Factory(Factory *this)

{
  *(undefined ***)this = &_vftable__for__Attachable__;
  *(undefined ***)&this->field_0x20 = &_vftable__for__DistributedObject__;
  Producer::~Producer((Producer *)this);
  return;
}
