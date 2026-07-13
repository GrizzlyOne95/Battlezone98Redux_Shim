/*
 * Entry: 0047f6bc
 * Name: stdext::unchecked_uninitialized_copy<Attachment_*_*,Attachment_*_*,std::allocator<Attachment_*>_>
 * Namespace: stdext
 * Signature: Attachment * * unchecked_uninitialized_copy<Attachment_*_*,Attachment_*_*,std::allocator<Attachment_*>_>(Attachment * * param_1, Attachment * * param_2, Attachment * * param_3, allocator<Attachment_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Attachment ** __cdecl
stdext::unchecked_uninitialized_copy<Attachment_*_*,Attachment_*_*,std::allocator<Attachment_*>_>
          (Attachment **param_1,Attachment **param_2,Attachment **param_3,
          allocator<Attachment_*> *param_4)

{
  Attachment **ppAVar1;
  
  ppAVar1 = std::_Uninit_copy<Attachment_*_*,Attachment_*_*,std::allocator<Attachment_*>_>
                      (param_1,param_2,param_3,param_4,SUB41(param_2,0),
                       (_Range_checked_iterator_tag)0x0);
  return ppAVar1;
}
