/*
 * Entry: 0053aa82
 * Name: SprayBombClass::`scalar_deleting_destructor'
 * Namespace: SprayBombClass
 * Signature: void * `scalar_deleting_destructor'(SprayBombClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SprayBombClass::_scalar_deleting_destructor_(SprayBombClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  GrenadeClass::~GrenadeClass((GrenadeClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
