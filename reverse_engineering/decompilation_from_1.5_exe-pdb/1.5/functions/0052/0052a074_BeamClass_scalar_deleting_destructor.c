/*
 * Entry: 0052a074
 * Name: BeamClass::`scalar_deleting_destructor'
 * Namespace: BeamClass
 * Signature: void * `scalar_deleting_destructor'(BeamClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall BeamClass::_scalar_deleting_destructor_(BeamClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  BulletClass::~BulletClass((BulletClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
