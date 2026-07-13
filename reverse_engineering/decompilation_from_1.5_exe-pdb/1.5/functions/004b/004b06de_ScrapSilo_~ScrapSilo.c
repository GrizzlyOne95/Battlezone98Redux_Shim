/*
 * Entry: 004b06de
 * Name: ScrapSilo::~ScrapSilo
 * Namespace: ScrapSilo
 * Signature: void ~ScrapSilo(ScrapSilo * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScrapSilo::~ScrapSilo(ScrapSilo *this)

{
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  Building::~Building((Building *)this);
  return;
}
