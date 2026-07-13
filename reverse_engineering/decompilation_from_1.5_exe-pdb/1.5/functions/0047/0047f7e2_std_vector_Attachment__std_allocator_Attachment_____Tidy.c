/*
 * Entry: 0047f7e2
 * Name: std::vector<Attachment_*,std::allocator<Attachment_*>_>::_Tidy
 * Namespace: std::vector<Attachment_*,std::allocator<Attachment_*>_>
 * Signature: void _Tidy(vector<Attachment_*,std::allocator<Attachment_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Attachment_*,std::allocator<Attachment_*>_>::_Tidy
          (vector<Attachment_*,std::allocator<Attachment_*>_> *this)

{
  if (this->_Myfirst != (Attachment **)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (Attachment **)0x0;
  this->_Mylast = (Attachment **)0x0;
  this->_Myend = (Attachment **)0x0;
  return;
}
