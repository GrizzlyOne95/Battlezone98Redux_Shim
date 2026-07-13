/*
 * Entry: 00489ab6
 * Name: CraftClass::`scalar_deleting_destructor'
 * Namespace: CraftClass
 * Signature: void * `scalar_deleting_destructor'(CraftClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall CraftClass::_scalar_deleting_destructor_(CraftClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
