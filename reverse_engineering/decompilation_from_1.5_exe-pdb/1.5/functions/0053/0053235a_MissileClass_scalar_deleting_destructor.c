/*
 * Entry: 0053235a
 * Name: MissileClass::`scalar_deleting_destructor'
 * Namespace: MissileClass
 * Signature: void * `scalar_deleting_destructor'(MissileClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall MissileClass::_scalar_deleting_destructor_(MissileClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  RocketClass::~RocketClass((RocketClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
