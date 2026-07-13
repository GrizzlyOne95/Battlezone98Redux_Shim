/*
 * Entry: 0047f556
 * Name: std::vector<Attachment_*,std::allocator<Attachment_*>_>::operator[]
 * Namespace: std::vector<Attachment_*,std::allocator<Attachment_*>_>
 * Signature: Attachment * * operator[](vector<Attachment_*,std::allocator<Attachment_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Attachment ** __thiscall
std::vector<Attachment_*,std::allocator<Attachment_*>_>::operator[]
          (vector<Attachment_*,std::allocator<Attachment_*>_> *this,uint param_1)

{
  if ((uint)((int)this->_Mylast - (int)this->_Myfirst >> 2) <= param_1) {
    _invalid_parameter_noinfo();
  }
  return this->_Myfirst + param_1;
}
