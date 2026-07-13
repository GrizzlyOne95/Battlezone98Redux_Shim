/*
 * Entry: 0052c780
 * Name: CannonClass::`scalar_deleting_destructor'
 * Namespace: CannonClass
 * Signature: void * `scalar_deleting_destructor'(CannonClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall CannonClass::_scalar_deleting_destructor_(CannonClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  WeaponClass::~WeaponClass((WeaponClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
