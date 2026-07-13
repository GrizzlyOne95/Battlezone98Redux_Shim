/*
 * Entry: 0047f77c
 * Name: stdext::_Unchecked_move_backward<Attachment_*_*,Attachment_*_*>
 * Namespace: stdext
 * Signature: Attachment * * _Unchecked_move_backward<Attachment_*_*,Attachment_*_*>(Attachment * * param_1, Attachment * * param_2, Attachment * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Attachment ** __cdecl
stdext::_Unchecked_move_backward<Attachment_*_*,Attachment_*_*>
          (Attachment **param_1,Attachment **param_2,Attachment **param_3)

{
  Attachment **ppAVar1;
  
  ppAVar1 = std::
            _Move_backward_opt<Attachment_*_*,Attachment_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Undefined_move_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppAVar1;
}
