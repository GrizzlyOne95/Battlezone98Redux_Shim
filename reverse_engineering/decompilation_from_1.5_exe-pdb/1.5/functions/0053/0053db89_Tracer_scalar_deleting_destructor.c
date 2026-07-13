/*
 * Entry: 0053db89
 * Name: Tracer::`scalar_deleting_destructor'
 * Namespace: Tracer
 * Signature: void * `scalar_deleting_destructor'(Tracer * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Tracer::_scalar_deleting_destructor_(Tracer *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  Bullet::~Bullet((Bullet *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
