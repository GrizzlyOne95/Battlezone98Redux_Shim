/*
 * Entry: 00497724
 * Name: stdext::unchecked_uninitialized_copy<GameObject_*_*,GameObject_*_*,std::allocator<GameObject_*>_>
 * Namespace: stdext
 * Signature: GameObject * * unchecked_uninitialized_copy<GameObject_*_*,GameObject_*_*,std::allocator<GameObject_*>_>(GameObject * * param_1, GameObject * * param_2, GameObject * * param_3, allocator<GameObject_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject ** __cdecl
stdext::unchecked_uninitialized_copy<GameObject_*_*,GameObject_*_*,std::allocator<GameObject_*>_>
          (GameObject **param_1,GameObject **param_2,GameObject **param_3,
          allocator<GameObject_*> *param_4)

{
  GameObject **ppGVar1;
  
  ppGVar1 = std::_Uninit_copy<GameObject_*_*,GameObject_*_*,std::allocator<GameObject_*>_>
                      (param_1,param_2,param_3,param_4,SUB41(param_2,0),
                       (_Range_checked_iterator_tag)0x0);
  return ppGVar1;
}
