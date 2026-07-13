/*
 * Entry: 004c177e
 * Name: HardPoints::`scalar_deleting_destructor'
 * Namespace: HardPoints
 * Signature: void * `scalar_deleting_destructor'(HardPoints * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall HardPoints::_scalar_deleting_destructor_(HardPoints *this,uint param_1)

{
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
