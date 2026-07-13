/*
 * Entry: 004c8e76
 * Name: DisplayInterface::`scalar_deleting_destructor'
 * Namespace: DisplayInterface
 * Signature: void * `scalar_deleting_destructor'(DisplayInterface * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
DisplayInterface::_scalar_deleting_destructor_(DisplayInterface *this,uint param_1)

{
  ~DisplayInterface(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
