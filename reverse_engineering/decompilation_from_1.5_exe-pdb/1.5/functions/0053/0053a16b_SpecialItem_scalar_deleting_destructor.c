/*
 * Entry: 0053a16b
 * Name: SpecialItem::`scalar_deleting_destructor'
 * Namespace: SpecialItem
 * Signature: void * `scalar_deleting_destructor'(SpecialItem * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SpecialItem::_scalar_deleting_destructor_(SpecialItem *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  Weapon::~Weapon((Weapon *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
