/*
 * Entry: 0047f41b
 * Name: Attachment::`scalar_deleting_destructor'
 * Namespace: Attachment
 * Signature: void * `scalar_deleting_destructor'(Attachment * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Attachment::_scalar_deleting_destructor_(Attachment *this,uint param_1)

{
  *this = (Attachment)&_vftable_;
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
