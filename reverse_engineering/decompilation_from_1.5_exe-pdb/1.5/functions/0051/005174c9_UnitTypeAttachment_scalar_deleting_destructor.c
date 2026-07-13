/*
 * Entry: 005174c9
 * Name: UnitTypeAttachment::`scalar_deleting_destructor'
 * Namespace: UnitTypeAttachment
 * Signature: void * `scalar_deleting_destructor'(UnitTypeAttachment * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
UnitTypeAttachment::_scalar_deleting_destructor_(UnitTypeAttachment *this,uint param_1)

{
  Attachment::~Attachment((Attachment *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
