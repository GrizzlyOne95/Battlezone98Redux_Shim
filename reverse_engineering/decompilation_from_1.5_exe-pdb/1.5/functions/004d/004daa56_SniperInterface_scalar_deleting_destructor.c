/*
 * Entry: 004daa56
 * Name: SniperInterface::`scalar_deleting_destructor'
 * Namespace: SniperInterface
 * Signature: void * `scalar_deleting_destructor'(SniperInterface * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SniperInterface::_scalar_deleting_destructor_(SniperInterface *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
