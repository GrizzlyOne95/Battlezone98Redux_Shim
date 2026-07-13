/*
 * Entry: 0052ad97
 * Name: BoltClass::`scalar_deleting_destructor'
 * Namespace: BoltClass
 * Signature: void * `scalar_deleting_destructor'(BoltClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall BoltClass::_scalar_deleting_destructor_(BoltClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  BulletClass::~BulletClass((BulletClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
