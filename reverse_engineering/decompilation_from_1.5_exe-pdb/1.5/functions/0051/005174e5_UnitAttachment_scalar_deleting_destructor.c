/*
 * Entry: 005174e5
 * Name: UnitAttachment::`scalar_deleting_destructor'
 * Namespace: UnitAttachment
 * Signature: void * `scalar_deleting_destructor'(UnitAttachment * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall UnitAttachment::_scalar_deleting_destructor_(UnitAttachment *this,uint param_1)

{
  ~UnitAttachment(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
