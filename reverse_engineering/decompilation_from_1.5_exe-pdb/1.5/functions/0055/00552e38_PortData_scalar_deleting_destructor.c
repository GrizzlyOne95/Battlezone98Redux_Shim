/*
 * Entry: 00552e38
 * Name: PortData::`scalar_deleting_destructor'
 * Namespace: PortData
 * Signature: void * `scalar_deleting_destructor'(PortData * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PortData::_scalar_deleting_destructor_(PortData *this,uint param_1)

{
  operator_delete__(this->name);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
