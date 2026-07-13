/*
 * Entry: 004c4138
 * Name: ControlPanel::`scalar_deleting_destructor'
 * Namespace: ControlPanel
 * Signature: void * `scalar_deleting_destructor'(ControlPanel * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ControlPanel::_scalar_deleting_destructor_(ControlPanel *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
