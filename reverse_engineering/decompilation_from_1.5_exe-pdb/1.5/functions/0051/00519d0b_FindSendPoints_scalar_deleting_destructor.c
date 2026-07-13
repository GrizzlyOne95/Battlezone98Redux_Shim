/*
 * Entry: 00519d0b
 * Name: FindSendPoints::`scalar_deleting_destructor'
 * Namespace: FindSendPoints
 * Signature: void * `scalar_deleting_destructor'(FindSendPoints * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall FindSendPoints::_scalar_deleting_destructor_(FindSendPoints *this,uint param_1)

{
  ~FindSendPoints(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
