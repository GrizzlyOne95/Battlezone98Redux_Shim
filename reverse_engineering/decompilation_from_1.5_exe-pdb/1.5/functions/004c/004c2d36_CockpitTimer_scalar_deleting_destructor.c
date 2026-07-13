/*
 * Entry: 004c2d36
 * Name: CockpitTimer::`scalar_deleting_destructor'
 * Namespace: CockpitTimer
 * Signature: void * `scalar_deleting_destructor'(CockpitTimer * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall CockpitTimer::_scalar_deleting_destructor_(CockpitTimer *this,uint param_1)

{
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
