/*
 * Entry: 0053269e
 * Name: ObjectLobber::`scalar_deleting_destructor'
 * Namespace: ObjectLobber
 * Signature: void * `scalar_deleting_destructor'(ObjectLobber * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ObjectLobber::_scalar_deleting_destructor_(ObjectLobber *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  Weapon::~Weapon((Weapon *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
