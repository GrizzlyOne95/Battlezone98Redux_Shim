/*
 * Entry: 004d13e8
 * Name: MapRadar::`scalar_deleting_destructor'
 * Namespace: MapRadar
 * Signature: void * `scalar_deleting_destructor'(MapRadar * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall MapRadar::_scalar_deleting_destructor_(MapRadar *this,uint param_1)

{
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
