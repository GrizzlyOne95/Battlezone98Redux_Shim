/*
 * Entry: 004bf3f2
 * Name: CockpitRadar::`scalar_deleting_destructor'
 * Namespace: CockpitRadar
 * Signature: void * `scalar_deleting_destructor'(CockpitRadar * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall CockpitRadar::_scalar_deleting_destructor_(CockpitRadar *this,uint param_1)

{
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
