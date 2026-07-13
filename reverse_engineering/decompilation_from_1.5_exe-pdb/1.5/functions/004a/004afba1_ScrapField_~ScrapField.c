/*
 * Entry: 004afba1
 * Name: ScrapField::~ScrapField
 * Namespace: ScrapField
 * Signature: void ~ScrapField(ScrapField * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScrapField::~ScrapField(ScrapField *this)

{
  *(undefined ***)this = &Building::_vftable__for__Attachable__;
  *(undefined ***)&this->field_0x20 = &Building::_vftable__for__DistributedObject__;
  GameObject::~GameObject((GameObject *)this);
  return;
}
