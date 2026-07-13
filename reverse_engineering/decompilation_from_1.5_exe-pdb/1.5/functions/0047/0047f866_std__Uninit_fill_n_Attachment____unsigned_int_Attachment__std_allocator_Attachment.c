/*
 * Entry: 0047f866
 * Name: std::_Uninit_fill_n<Attachment_*_*,unsigned_int,Attachment_*,std::allocator<Attachment_*>_>
 * Namespace: std
 * Signature: void _Uninit_fill_n<Attachment_*_*,unsigned_int,Attachment_*,std::allocator<Attachment_*>_>(Attachment * * param_1, uint param_2, Attachment * * param_3, allocator<Attachment_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Uninit_fill_n<Attachment_*_*,unsigned_int,Attachment_*,std::allocator<Attachment_*>_>
          (Attachment **param_1,uint param_2,Attachment **param_3,allocator<Attachment_*> *param_4,
          _Scalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  stdext::unchecked_fill_n<Attachment_*_*,unsigned_int,Attachment_*>(param_1,param_2,param_3);
  return;
}
