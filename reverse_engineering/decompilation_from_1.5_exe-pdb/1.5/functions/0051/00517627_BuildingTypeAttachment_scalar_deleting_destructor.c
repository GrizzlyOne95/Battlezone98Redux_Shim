/*
 * Entry: 00517627
 * Name: BuildingTypeAttachment::`scalar_deleting_destructor'
 * Namespace: BuildingTypeAttachment
 * Signature: void * `scalar_deleting_destructor'(BuildingTypeAttachment * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
BuildingTypeAttachment::_scalar_deleting_destructor_(BuildingTypeAttachment *this,uint param_1)

{
  Attachment::~Attachment((Attachment *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
