/*
 * Entry: 0053b19f
 * Name: TargetingGunClass::`scalar_deleting_destructor'
 * Namespace: TargetingGunClass
 * Signature: void * `scalar_deleting_destructor'(TargetingGunClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
TargetingGunClass::_scalar_deleting_destructor_(TargetingGunClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  WeaponClass::~WeaponClass((WeaponClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
