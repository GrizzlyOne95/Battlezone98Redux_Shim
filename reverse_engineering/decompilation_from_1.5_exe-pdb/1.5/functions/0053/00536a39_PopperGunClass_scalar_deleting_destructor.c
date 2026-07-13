/*
 * Entry: 00536a39
 * Name: PopperGunClass::`scalar_deleting_destructor'
 * Namespace: PopperGunClass
 * Signature: void * `scalar_deleting_destructor'(PopperGunClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PopperGunClass::_scalar_deleting_destructor_(PopperGunClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  WeaponClass::~WeaponClass((WeaponClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
