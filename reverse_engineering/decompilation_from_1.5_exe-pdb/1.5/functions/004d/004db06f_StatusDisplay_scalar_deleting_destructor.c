/*
 * Entry: 004db06f
 * Name: StatusDisplay::`scalar_deleting_destructor'
 * Namespace: StatusDisplay
 * Signature: void * `scalar_deleting_destructor'(StatusDisplay * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall StatusDisplay::_scalar_deleting_destructor_(StatusDisplay *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
