/*
 * Entry: 0047f87b
 * Name: std::vector<Attachment_*,std::allocator<Attachment_*>_>::~vector<Attachment_*,std::allocator<Attachment_*>_>
 * Namespace: std::vector<Attachment_*,std::allocator<Attachment_*>_>
 * Signature: void ~vector<Attachment_*,std::allocator<Attachment_*>_>(vector<Attachment_*,std::allocator<Attachment_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Attachment_*,std::allocator<Attachment_*>_>::
~vector<Attachment_*,std::allocator<Attachment_*>_>
          (vector<Attachment_*,std::allocator<Attachment_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
