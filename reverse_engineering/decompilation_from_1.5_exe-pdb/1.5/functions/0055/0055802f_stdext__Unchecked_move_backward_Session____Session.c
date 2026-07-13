/*
 * Entry: 0055802f
 * Name: stdext::_Unchecked_move_backward<Session_*_*,Session_*_*>
 * Namespace: stdext
 * Signature: Session * * _Unchecked_move_backward<Session_*_*,Session_*_*>(Session * * param_1, Session * * param_2, Session * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Session ** __cdecl
stdext::_Unchecked_move_backward<Session_*_*,Session_*_*>
          (Session **param_1,Session **param_2,Session **param_3)

{
  Session **ppSVar1;
  
  ppSVar1 = std::
            _Move_backward_opt<Session_*_*,Session_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Undefined_move_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppSVar1;
}
