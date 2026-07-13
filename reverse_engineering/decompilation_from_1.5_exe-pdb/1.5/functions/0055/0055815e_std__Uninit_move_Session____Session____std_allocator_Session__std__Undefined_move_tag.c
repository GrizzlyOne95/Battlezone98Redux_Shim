/*
 * Entry: 0055815e
 * Name: std::_Uninit_move<Session_*_*,Session_*_*,std::allocator<Session_*>,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: Session * * _Uninit_move<Session_*_*,Session_*_*,std::allocator<Session_*>,std::_Undefined_move_tag>(Session * * param_1, Session * * param_2, Session * * param_3, allocator<Session_*> * param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Session ** __cdecl
std::_Uninit_move<Session_*_*,Session_*_*,std::allocator<Session_*>,std::_Undefined_move_tag>
          (Session **param_1,Session **param_2,Session **param_3,allocator<Session_*> *param_4,
          _Undefined_move_tag param_5,_Range_checked_iterator_tag param_6)

{
  Session **ppSVar1;
  
  ppSVar1 = stdext::unchecked_uninitialized_copy<Session_*_*,Session_*_*,std::allocator<Session_*>_>
                      (param_1,param_2,param_3,param_4);
  return ppSVar1;
}
