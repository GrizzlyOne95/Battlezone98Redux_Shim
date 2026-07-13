/*
 * Entry: 00497a7f
 * Name: stdext::_Unchecked_uninitialized_move<std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>,GameObject_*_*,std::allocator<GameObject_*>_>
 * Namespace: stdext
 * Signature: GameObject * * _Unchecked_uninitialized_move<std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>,GameObject_*_*,std::allocator<GameObject_*>_>(_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> param_1, _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> param_2, GameObject * * param_3, allocator<GameObject_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject ** __cdecl
stdext::
_Unchecked_uninitialized_move<std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>,GameObject_*_*,std::allocator<GameObject_*>_>
          (_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> param_1,
          _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> param_2,GameObject **param_3,
          allocator<GameObject_*> *param_4)

{
  GameObject **ppGVar1;
  
  ppGVar1 = unchecked_uninitialized_copy<GameObject_*_*,GameObject_*_*,std::allocator<GameObject_*>_>
                      ((GameObject **)param_1._4_4_,(GameObject **)param_2._4_4_,param_3,param_4);
  return ppGVar1;
}
