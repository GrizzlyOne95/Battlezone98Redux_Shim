/*
 * Entry: 00530c8d
 * Name: LauncherInterface::`scalar_deleting_destructor'
 * Namespace: LauncherInterface
 * Signature: void * `scalar_deleting_destructor'(LauncherInterface * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
LauncherInterface::_scalar_deleting_destructor_(LauncherInterface *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
