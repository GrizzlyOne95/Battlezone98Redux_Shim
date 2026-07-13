/*
 * Entry: 0047f722
 * Name: std::_Vector_iterator<Attachment_*,std::allocator<Attachment_*>_>::operator+=
 * Namespace: std::_Vector_iterator<Attachment_*,std::allocator<Attachment_*>_>
 * Signature: _Vector_iterator<Attachment_*,std::allocator<Attachment_*>_> * operator+=(_Vector_iterator<Attachment_*,std::allocator<Attachment_*>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Attachment_*,std::allocator<Attachment_*>_> * __thiscall
std::_Vector_iterator<Attachment_*,std::allocator<Attachment_*>_>::operator+=
          (_Vector_iterator<Attachment_*,std::allocator<Attachment_*>_> *this,int param_1)

{
  _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_>::operator+=
            ((_Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_> *)this,param_1);
  return this;
}
