/*
 * Entry: 00498224
 * Name: std::vector<Attachment_*,std::allocator<Attachment_*>_>::vector<Attachment_*,std::allocator<Attachment_*>_>
 * Namespace: std::vector<Attachment_*,std::allocator<Attachment_*>_>
 * Signature: vector<Attachment_*,std::allocator<Attachment_*>_> * vector<Attachment_*,std::allocator<Attachment_*>_>(vector<Attachment_*,std::allocator<Attachment_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

vector<Attachment_*,std::allocator<Attachment_*>_> * __thiscall
std::vector<Attachment_*,std::allocator<Attachment_*>_>::
vector<Attachment_*,std::allocator<Attachment_*>_>
          (vector<Attachment_*,std::allocator<Attachment_*>_> *this)

{
  _Vector_val<Attachment_*,std::allocator<Attachment_*>_>::
  _Vector_val<Attachment_*,std::allocator<Attachment_*>_>
            ((_Vector_val<Attachment_*,std::allocator<Attachment_*>_> *)this,SUB41(this,0));
  _Buy(this,0);
  return this;
}
