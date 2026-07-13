/*
 * Entry: 0047f8a3
 * Name: std::vector<Attachment_*,std::allocator<Attachment_*>_>::_Umove<Attachment_*_*>
 * Namespace: std::vector<Attachment_*,std::allocator<Attachment_*>_>
 * Signature: Attachment * * _Umove<Attachment_*_*>(vector<Attachment_*,std::allocator<Attachment_*>_> * this, Attachment * * param_1, Attachment * * param_2, Attachment * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Attachment ** __thiscall
std::vector<Attachment_*,std::allocator<Attachment_*>_>::_Umove<Attachment_*_*>
          (vector<Attachment_*,std::allocator<Attachment_*>_> *this,Attachment **param_1,
          Attachment **param_2,Attachment **param_3)

{
  Attachment **ppAVar1;
  
  ppAVar1 = stdext::
            unchecked_uninitialized_copy<Attachment_*_*,Attachment_*_*,std::allocator<Attachment_*>_>
                      (param_1,param_2,param_3,(allocator<Attachment_*> *)&this->_padding_);
  return ppAVar1;
}
