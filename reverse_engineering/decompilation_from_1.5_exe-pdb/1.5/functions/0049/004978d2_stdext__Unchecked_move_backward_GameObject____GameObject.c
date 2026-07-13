/*
 * Entry: 004978d2
 * Name: stdext::_Unchecked_move_backward<GameObject_*_*,GameObject_*_*>
 * Namespace: stdext
 * Signature: GameObject * * _Unchecked_move_backward<GameObject_*_*,GameObject_*_*>(GameObject * * param_1, GameObject * * param_2, GameObject * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject ** __cdecl
stdext::_Unchecked_move_backward<GameObject_*_*,GameObject_*_*>
          (GameObject **param_1,GameObject **param_2,GameObject **param_3)

{
  GameObject **ppGVar1;
  
  ppGVar1 = std::
            _Move_backward_opt<GameObject_*_*,GameObject_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Undefined_move_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppGVar1;
}
