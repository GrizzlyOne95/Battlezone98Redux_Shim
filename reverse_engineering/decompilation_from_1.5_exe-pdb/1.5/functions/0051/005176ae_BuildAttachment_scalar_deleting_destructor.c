/*
 * Entry: 005176ae
 * Name: BuildAttachment::`scalar_deleting_destructor'
 * Namespace: BuildAttachment
 * Signature: void * `scalar_deleting_destructor'(BuildAttachment * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall BuildAttachment::_scalar_deleting_destructor_(BuildAttachment *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  Attachment::~Attachment((Attachment *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
