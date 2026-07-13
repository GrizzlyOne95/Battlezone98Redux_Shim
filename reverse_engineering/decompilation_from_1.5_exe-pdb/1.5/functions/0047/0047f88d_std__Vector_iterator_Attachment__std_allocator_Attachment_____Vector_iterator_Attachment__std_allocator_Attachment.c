/*
 * Entry: 0047f88d
 * Name: std::_Vector_iterator<Attachment_*,std::allocator<Attachment_*>_>::_Vector_iterator<Attachment_*,std::allocator<Attachment_*>_>
 * Namespace: std::_Vector_iterator<Attachment_*,std::allocator<Attachment_*>_>
 * Signature: _Vector_iterator<Attachment_*,std::allocator<Attachment_*>_> * _Vector_iterator<Attachment_*,std::allocator<Attachment_*>_>(_Vector_iterator<Attachment_*,std::allocator<Attachment_*>_> * this, Attachment * * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Attachment_*,std::allocator<Attachment_*>_> * __thiscall
std::_Vector_iterator<Attachment_*,std::allocator<Attachment_*>_>::
_Vector_iterator<Attachment_*,std::allocator<Attachment_*>_>
          (_Vector_iterator<Attachment_*,std::allocator<Attachment_*>_> *this,Attachment **param_1,
          _Container_base_aux *param_2)

{
  _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_>::
  _Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_>
            ((_Vector_const_iterator<Attachment_*,std::allocator<Attachment_*>_> *)this,param_1,
             param_2);
  return this;
}
