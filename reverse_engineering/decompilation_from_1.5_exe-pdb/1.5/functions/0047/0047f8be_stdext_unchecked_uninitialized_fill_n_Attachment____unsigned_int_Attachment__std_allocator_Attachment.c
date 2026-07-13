/*
 * Entry: 0047f8be
 * Name: stdext::unchecked_uninitialized_fill_n<Attachment_*_*,unsigned_int,Attachment_*,std::allocator<Attachment_*>_>
 * Namespace: stdext
 * Signature: void unchecked_uninitialized_fill_n<Attachment_*_*,unsigned_int,Attachment_*,std::allocator<Attachment_*>_>(Attachment * * param_1, uint param_2, Attachment * * param_3, allocator<Attachment_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::
unchecked_uninitialized_fill_n<Attachment_*_*,unsigned_int,Attachment_*,std::allocator<Attachment_*>_>
          (Attachment **param_1,uint param_2,Attachment **param_3,allocator<Attachment_*> *param_4)

{
  unchecked_fill_n<Attachment_*_*,unsigned_int,Attachment_*>(param_1,param_2,param_3);
  return;
}
