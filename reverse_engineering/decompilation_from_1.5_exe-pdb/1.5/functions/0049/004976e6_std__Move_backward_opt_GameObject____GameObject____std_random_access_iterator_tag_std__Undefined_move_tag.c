/*
 * Entry: 004976e6
 * Name: std::_Move_backward_opt<GameObject_*_*,GameObject_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: GameObject * * _Move_backward_opt<GameObject_*_*,GameObject_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>(GameObject * * param_1, GameObject * * param_2, GameObject * * param_3, random_access_iterator_tag param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject ** __cdecl
std::
_Move_backward_opt<GameObject_*_*,GameObject_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
          (GameObject **param_1,GameObject **param_2,GameObject **param_3,
          random_access_iterator_tag param_4,_Undefined_move_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  GameObject **ppGVar1;
  
  ppGVar1 = _Copy_backward_opt<GameObject_*_*,GameObject_*_*,std::random_access_iterator_tag>
                      (param_1,param_2,param_3,param_4,(_Scalar_ptr_iterator_tag)0x0,
                       (_Range_checked_iterator_tag)0x0);
  return ppGVar1;
}
