/*
 * Entry: 00537e8d
 * Name: Rocket::`scalar_deleting_destructor'
 * Namespace: Rocket
 * Signature: void * `scalar_deleting_destructor'(Rocket * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Rocket::_scalar_deleting_destructor_(Rocket *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  Bullet::~Bullet((Bullet *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
