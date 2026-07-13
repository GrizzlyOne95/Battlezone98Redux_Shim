/*
 * Entry: 00516445
 * Name: BuildAttachment::~BuildAttachment
 * Namespace: BuildAttachment
 * Signature: void ~BuildAttachment(BuildAttachment * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BuildAttachment::~BuildAttachment(BuildAttachment *this)

{
  this->_padding_ = (int)&_vftable_;
  Attachment::~Attachment((Attachment *)this);
  return;
}
