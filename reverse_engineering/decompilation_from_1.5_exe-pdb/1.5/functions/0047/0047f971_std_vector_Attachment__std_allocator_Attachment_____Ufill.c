/*
 * Entry: 0047f971
 * Name: std::vector<Attachment_*,std::allocator<Attachment_*>_>::_Ufill
 * Namespace: std::vector<Attachment_*,std::allocator<Attachment_*>_>
 * Signature: Attachment * * _Ufill(vector<Attachment_*,std::allocator<Attachment_*>_> * this, Attachment * * param_1, uint param_2, Attachment * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Attachment ** __thiscall
std::vector<Attachment_*,std::allocator<Attachment_*>_>::_Ufill
          (vector<Attachment_*,std::allocator<Attachment_*>_> *this,Attachment **param_1,
          uint param_2,Attachment **param_3)

{
  stdext::unchecked_fill_n<Attachment_*_*,unsigned_int,Attachment_*>(param_1,param_2,param_3);
  return param_1 + param_2;
}
