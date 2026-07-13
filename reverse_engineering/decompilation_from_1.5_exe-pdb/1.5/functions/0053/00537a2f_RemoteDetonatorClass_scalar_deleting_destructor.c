/*
 * Entry: 00537a2f
 * Name: RemoteDetonatorClass::`scalar_deleting_destructor'
 * Namespace: RemoteDetonatorClass
 * Signature: void * `scalar_deleting_destructor'(RemoteDetonatorClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
RemoteDetonatorClass::_scalar_deleting_destructor_(RemoteDetonatorClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  MortarClass::~MortarClass((MortarClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
