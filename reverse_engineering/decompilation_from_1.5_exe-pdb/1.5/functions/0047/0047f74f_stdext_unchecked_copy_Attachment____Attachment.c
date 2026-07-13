/*
 * Entry: 0047f74f
 * Name: stdext::unchecked_copy<Attachment_*_*,Attachment_*_*>
 * Namespace: stdext
 * Signature: Attachment * * unchecked_copy<Attachment_*_*,Attachment_*_*>(Attachment * * param_1, Attachment * * param_2, Attachment * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Attachment ** __cdecl
stdext::unchecked_copy<Attachment_*_*,Attachment_*_*>
          (Attachment **param_1,Attachment **param_2,Attachment **param_3)

{
  Attachment **ppAVar1;
  
  ppAVar1 = std::_Copy_opt<Attachment_*_*,Attachment_*_*,std::random_access_iterator_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Scalar_ptr_iterator_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppAVar1;
}
