/*
 * Entry: 004d5452
 * Name: PathDisplay::`scalar_deleting_destructor'
 * Namespace: PathDisplay
 * Signature: void * `scalar_deleting_destructor'(PathDisplay * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PathDisplay::_scalar_deleting_destructor_(PathDisplay *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
