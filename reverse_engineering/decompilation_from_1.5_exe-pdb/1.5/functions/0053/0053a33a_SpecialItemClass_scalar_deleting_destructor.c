/*
 * Entry: 0053a33a
 * Name: SpecialItemClass::`scalar_deleting_destructor'
 * Namespace: SpecialItemClass
 * Signature: void * `scalar_deleting_destructor'(SpecialItemClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
SpecialItemClass::_scalar_deleting_destructor_(SpecialItemClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  WeaponClass::~WeaponClass((WeaponClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
