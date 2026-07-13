/*
 * Entry: 0052b59e
 * Name: BounceBombClass::`scalar_deleting_destructor'
 * Namespace: BounceBombClass
 * Signature: void * `scalar_deleting_destructor'(BounceBombClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall BounceBombClass::_scalar_deleting_destructor_(BounceBombClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  GrenadeClass::~GrenadeClass((GrenadeClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
