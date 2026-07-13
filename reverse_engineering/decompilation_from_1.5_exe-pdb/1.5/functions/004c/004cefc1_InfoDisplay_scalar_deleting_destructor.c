/*
 * Entry: 004cefc1
 * Name: InfoDisplay::`scalar_deleting_destructor'
 * Namespace: InfoDisplay
 * Signature: void * `scalar_deleting_destructor'(InfoDisplay * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall InfoDisplay::_scalar_deleting_destructor_(InfoDisplay *this,uint param_1)

{
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
