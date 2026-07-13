/*
 * Entry: 00537413
 * Name: RadarDamper::`scalar_deleting_destructor'
 * Namespace: RadarDamper
 * Signature: void * `scalar_deleting_destructor'(RadarDamper * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall RadarDamper::_scalar_deleting_destructor_(RadarDamper *this,uint param_1)

{
  ~RadarDamper(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
