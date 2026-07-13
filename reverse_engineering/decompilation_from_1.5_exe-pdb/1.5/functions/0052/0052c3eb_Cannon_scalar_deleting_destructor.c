/*
 * Entry: 0052c3eb
 * Name: Cannon::`scalar_deleting_destructor'
 * Namespace: Cannon
 * Signature: void * `scalar_deleting_destructor'(Cannon * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Cannon::_scalar_deleting_destructor_(Cannon *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  Weapon::~Weapon((Weapon *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
