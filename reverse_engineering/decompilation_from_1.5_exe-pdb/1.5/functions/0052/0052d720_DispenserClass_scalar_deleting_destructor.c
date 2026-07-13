/*
 * Entry: 0052d720
 * Name: DispenserClass::`scalar_deleting_destructor'
 * Namespace: DispenserClass
 * Signature: void * `scalar_deleting_destructor'(DispenserClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall DispenserClass::_scalar_deleting_destructor_(DispenserClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  WeaponClass::~WeaponClass((WeaponClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
