/*
 * Entry: 0053676a
 * Name: PopperGun::`scalar_deleting_destructor'
 * Namespace: PopperGun
 * Signature: void * `scalar_deleting_destructor'(PopperGun * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PopperGun::_scalar_deleting_destructor_(PopperGun *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  Weapon::~Weapon((Weapon *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
