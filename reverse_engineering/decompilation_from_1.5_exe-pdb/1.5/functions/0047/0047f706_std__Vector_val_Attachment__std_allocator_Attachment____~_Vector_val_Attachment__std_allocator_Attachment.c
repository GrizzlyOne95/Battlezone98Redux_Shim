/*
 * Entry: 0047f706
 * Name: std::_Vector_val<Attachment_*,std::allocator<Attachment_*>_>::~_Vector_val<Attachment_*,std::allocator<Attachment_*>_>
 * Namespace: std::_Vector_val<Attachment_*,std::allocator<Attachment_*>_>
 * Signature: void ~_Vector_val<Attachment_*,std::allocator<Attachment_*>_>(_Vector_val<Attachment_*,std::allocator<Attachment_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<Attachment_*,std::allocator<Attachment_*>_>::
~_Vector_val<Attachment_*,std::allocator<Attachment_*>_>
          (_Vector_val<Attachment_*,std::allocator<Attachment_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
