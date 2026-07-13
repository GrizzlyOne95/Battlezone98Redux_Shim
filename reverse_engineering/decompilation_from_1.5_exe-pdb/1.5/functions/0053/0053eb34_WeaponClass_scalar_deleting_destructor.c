/*
 * Entry: 0053eb34
 * Name: WeaponClass::`scalar_deleting_destructor'
 * Namespace: WeaponClass
 * Signature: void * `scalar_deleting_destructor'(WeaponClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall WeaponClass::_scalar_deleting_destructor_(WeaponClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
