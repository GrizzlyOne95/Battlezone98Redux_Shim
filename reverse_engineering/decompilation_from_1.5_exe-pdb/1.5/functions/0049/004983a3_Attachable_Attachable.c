/*
 * Entry: 004983a3
 * Name: Attachable::Attachable
 * Namespace: Attachable
 * Signature: Attachable * Attachable(Attachable * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Attachable * __thiscall Attachable::Attachable(Attachable *this)

{
  this->_padding_ = (int)&_vftable_;
  std::vector<Attachment_*,std::allocator<Attachment_*>_>::
  vector<Attachment_*,std::allocator<Attachment_*>_>(&this->attachments);
  return this;
}
