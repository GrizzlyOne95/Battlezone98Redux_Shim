/*
 * Entry: 004a5316
 * Name: Person::~Person
 * Namespace: Person
 * Signature: void ~Person(Person * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Person::~Person(Person *this)

{
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  Craft::~Craft((Craft *)this);
  return;
}
