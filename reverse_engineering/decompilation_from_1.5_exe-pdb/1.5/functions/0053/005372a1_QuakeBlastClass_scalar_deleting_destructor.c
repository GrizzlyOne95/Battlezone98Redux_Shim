/*
 * Entry: 005372a1
 * Name: QuakeBlastClass::`scalar_deleting_destructor'
 * Namespace: QuakeBlastClass
 * Signature: void * `scalar_deleting_destructor'(QuakeBlastClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall QuakeBlastClass::_scalar_deleting_destructor_(QuakeBlastClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  ExplosionClass::~ExplosionClass((ExplosionClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
