/*
 * Entry: 004b8bfe
 * Name: WalkerClass::`scalar_deleting_destructor'
 * Namespace: WalkerClass
 * Signature: void * `scalar_deleting_destructor'(WalkerClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall WalkerClass::_scalar_deleting_destructor_(WalkerClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  CraftClass::~CraftClass((CraftClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
