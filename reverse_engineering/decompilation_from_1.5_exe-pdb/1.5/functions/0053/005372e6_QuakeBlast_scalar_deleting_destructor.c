/*
 * Entry: 005372e6
 * Name: QuakeBlast::`scalar_deleting_destructor'
 * Namespace: QuakeBlast
 * Signature: void * `scalar_deleting_destructor'(QuakeBlast * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall QuakeBlast::_scalar_deleting_destructor_(QuakeBlast *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  Explosion::~Explosion((Explosion *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
