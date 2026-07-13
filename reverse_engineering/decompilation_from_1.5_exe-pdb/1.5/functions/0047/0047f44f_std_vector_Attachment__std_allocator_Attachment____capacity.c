/*
 * Entry: 0047f44f
 * Name: std::vector<Attachment_*,std::allocator<Attachment_*>_>::capacity
 * Namespace: std::vector<Attachment_*,std::allocator<Attachment_*>_>
 * Signature: uint capacity(vector<Attachment_*,std::allocator<Attachment_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<Attachment_*,std::allocator<Attachment_*>_>::capacity
          (vector<Attachment_*,std::allocator<Attachment_*>_> *this)

{
  if (this->_Myfirst == (Attachment **)0x0) {
    return 0;
  }
  return (int)this->_Myend - (int)this->_Myfirst >> 2;
}
