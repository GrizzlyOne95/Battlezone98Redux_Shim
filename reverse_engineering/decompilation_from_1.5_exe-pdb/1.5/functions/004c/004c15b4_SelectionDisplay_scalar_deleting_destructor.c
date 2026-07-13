/*
 * Entry: 004c15b4
 * Name: SelectionDisplay::`scalar_deleting_destructor'
 * Namespace: SelectionDisplay
 * Signature: void * `scalar_deleting_destructor'(SelectionDisplay * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
SelectionDisplay::_scalar_deleting_destructor_(SelectionDisplay *this,uint param_1)

{
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
