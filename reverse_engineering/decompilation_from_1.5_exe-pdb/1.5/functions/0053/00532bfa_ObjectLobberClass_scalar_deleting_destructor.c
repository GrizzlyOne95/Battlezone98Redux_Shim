/*
 * Entry: 00532bfa
 * Name: ObjectLobberClass::`scalar_deleting_destructor'
 * Namespace: ObjectLobberClass
 * Signature: void * `scalar_deleting_destructor'(ObjectLobberClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
ObjectLobberClass::_scalar_deleting_destructor_(ObjectLobberClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  WeaponClass::~WeaponClass((WeaponClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
