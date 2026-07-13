/*
 * Entry: 0047f7a4
 * Name: std::_Uninit_move<Attachment_*_*,Attachment_*_*,std::allocator<Attachment_*>,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: Attachment * * _Uninit_move<Attachment_*_*,Attachment_*_*,std::allocator<Attachment_*>,std::_Undefined_move_tag>(Attachment * * param_1, Attachment * * param_2, Attachment * * param_3, allocator<Attachment_*> * param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Attachment ** __cdecl
std::
_Uninit_move<Attachment_*_*,Attachment_*_*,std::allocator<Attachment_*>,std::_Undefined_move_tag>
          (Attachment **param_1,Attachment **param_2,Attachment **param_3,
          allocator<Attachment_*> *param_4,_Undefined_move_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  Attachment **ppAVar1;
  
  ppAVar1 = stdext::
            unchecked_uninitialized_copy<Attachment_*_*,Attachment_*_*,std::allocator<Attachment_*>_>
                      (param_1,param_2,param_3,param_4);
  return ppAVar1;
}
