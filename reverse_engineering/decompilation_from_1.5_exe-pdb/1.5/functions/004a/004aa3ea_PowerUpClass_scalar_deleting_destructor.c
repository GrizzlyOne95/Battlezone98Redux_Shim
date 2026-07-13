/*
 * Entry: 004aa3ea
 * Name: PowerUpClass::`scalar_deleting_destructor'
 * Namespace: PowerUpClass
 * Signature: void * `scalar_deleting_destructor'(PowerUpClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PowerUpClass::_scalar_deleting_destructor_(PowerUpClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
