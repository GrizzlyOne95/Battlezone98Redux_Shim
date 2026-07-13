/*
 * Entry: 00531fd1
 * Name: Missile::`scalar_deleting_destructor'
 * Namespace: Missile
 * Signature: void * `scalar_deleting_destructor'(Missile * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Missile::_scalar_deleting_destructor_(Missile *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  Rocket::~Rocket((Rocket *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
