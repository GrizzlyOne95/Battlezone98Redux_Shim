/*
 * Entry: 0047f694
 * Name: std::_Move_backward_opt<Attachment_*_*,Attachment_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: Attachment * * _Move_backward_opt<Attachment_*_*,Attachment_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>(Attachment * * param_1, Attachment * * param_2, Attachment * * param_3, random_access_iterator_tag param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Attachment ** __cdecl
std::
_Move_backward_opt<Attachment_*_*,Attachment_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
          (Attachment **param_1,Attachment **param_2,Attachment **param_3,
          random_access_iterator_tag param_4,_Undefined_move_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  Attachment **ppAVar1;
  
  ppAVar1 = _Copy_backward_opt<Attachment_*_*,Attachment_*_*,std::random_access_iterator_tag>
                      (param_1,param_2,param_3,param_4,(_Scalar_ptr_iterator_tag)0x0,
                       (_Range_checked_iterator_tag)0x0);
  return ppAVar1;
}
