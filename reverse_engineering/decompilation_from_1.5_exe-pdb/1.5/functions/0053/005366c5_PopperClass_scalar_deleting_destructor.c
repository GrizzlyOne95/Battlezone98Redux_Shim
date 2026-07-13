/*
 * Entry: 005366c5
 * Name: PopperClass::`scalar_deleting_destructor'
 * Namespace: PopperClass
 * Signature: void * `scalar_deleting_destructor'(PopperClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PopperClass::_scalar_deleting_destructor_(PopperClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  GrenadeClass::~GrenadeClass((GrenadeClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
