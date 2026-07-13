/*
 * Entry: 0049794f
 * Name: std::_Uninit_move<GameObject_*_*,GameObject_*_*,std::allocator<GameObject_*>,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: GameObject * * _Uninit_move<GameObject_*_*,GameObject_*_*,std::allocator<GameObject_*>,std::_Undefined_move_tag>(GameObject * * param_1, GameObject * * param_2, GameObject * * param_3, allocator<GameObject_*> * param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject ** __cdecl
std::
_Uninit_move<GameObject_*_*,GameObject_*_*,std::allocator<GameObject_*>,std::_Undefined_move_tag>
          (GameObject **param_1,GameObject **param_2,GameObject **param_3,
          allocator<GameObject_*> *param_4,_Undefined_move_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  GameObject **ppGVar1;
  
  ppGVar1 = stdext::
            unchecked_uninitialized_copy<GameObject_*_*,GameObject_*_*,std::allocator<GameObject_*>_>
                      (param_1,param_2,param_3,param_4);
  return ppGVar1;
}
