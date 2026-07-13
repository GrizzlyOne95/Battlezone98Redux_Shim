/*
 * Entry: 00539e97
 * Name: SpecialItem::~SpecialItem
 * Namespace: SpecialItem
 * Signature: void ~SpecialItem(SpecialItem * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SpecialItem::~SpecialItem(SpecialItem *this)

{
  this->_padding_ = (int)&_vftable_;
  Weapon::~Weapon((Weapon *)this);
  return;
}
