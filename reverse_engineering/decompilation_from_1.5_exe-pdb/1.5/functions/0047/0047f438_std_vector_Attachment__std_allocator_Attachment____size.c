/*
 * Entry: 0047f438
 * Name: std::vector<Attachment_*,std::allocator<Attachment_*>_>::size
 * Namespace: std::vector<Attachment_*,std::allocator<Attachment_*>_>
 * Signature: uint size(vector<Attachment_*,std::allocator<Attachment_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<Attachment_*,std::allocator<Attachment_*>_>::size
          (vector<Attachment_*,std::allocator<Attachment_*>_> *this)

{
  return (int)this->_Mylast - (int)this->_Myfirst >> 2;
}
