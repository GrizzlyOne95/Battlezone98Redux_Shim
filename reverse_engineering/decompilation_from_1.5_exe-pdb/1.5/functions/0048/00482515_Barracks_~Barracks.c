/*
 * Entry: 00482515
 * Name: Barracks::~Barracks
 * Namespace: Barracks
 * Signature: void ~Barracks(Barracks * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Barracks::~Barracks(Barracks *this)

{
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  Building::~Building((Building *)this);
  return;
}
