/*
 * Entry: 0047f4ff
 * Name: std::_Uninit_copy<Attachment_*_*,Attachment_*_*,std::allocator<Attachment_*>_>
 * Namespace: std
 * Signature: Attachment * * _Uninit_copy<Attachment_*_*,Attachment_*_*,std::allocator<Attachment_*>_>(Attachment * * param_1, Attachment * * param_2, Attachment * * param_3, allocator<Attachment_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Attachment ** __cdecl
std::_Uninit_copy<Attachment_*_*,Attachment_*_*,std::allocator<Attachment_*>_>
          (Attachment **param_1,Attachment **param_2,Attachment **param_3,
          allocator<Attachment_*> *param_4,_Scalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  int iVar1;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  if (iVar1 != 0) {
    memmove_s(param_3,iVar1 * 4,param_1,iVar1 * 4);
  }
  return param_3 + iVar1;
}
