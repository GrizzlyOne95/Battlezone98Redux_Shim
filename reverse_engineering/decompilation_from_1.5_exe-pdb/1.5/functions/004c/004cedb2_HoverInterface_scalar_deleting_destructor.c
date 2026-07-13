/*
 * Entry: 004cedb2
 * Name: HoverInterface::`scalar_deleting_destructor'
 * Namespace: HoverInterface
 * Signature: void * `scalar_deleting_destructor'(HoverInterface * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall HoverInterface::_scalar_deleting_destructor_(HoverInterface *this,uint param_1)

{
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
