/*
 * Entry: 0053da28
 * Name: TracerClass::`scalar_deleting_destructor'
 * Namespace: TracerClass
 * Signature: void * `scalar_deleting_destructor'(TracerClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall TracerClass::_scalar_deleting_destructor_(TracerClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  BulletClass::~BulletClass((BulletClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
