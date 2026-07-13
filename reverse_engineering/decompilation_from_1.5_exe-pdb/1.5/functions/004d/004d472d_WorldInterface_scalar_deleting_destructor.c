/*
 * Entry: 004d472d
 * Name: WorldInterface::`scalar_deleting_destructor'
 * Namespace: WorldInterface
 * Signature: void * `scalar_deleting_destructor'(WorldInterface * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall WorldInterface::_scalar_deleting_destructor_(WorldInterface *this,uint param_1)

{
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
