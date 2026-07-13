/*
 * Entry: 004978a5
 * Name: stdext::unchecked_copy<GameObject_*_*,GameObject_*_*>
 * Namespace: stdext
 * Signature: GameObject * * unchecked_copy<GameObject_*_*,GameObject_*_*>(GameObject * * param_1, GameObject * * param_2, GameObject * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject ** __cdecl
stdext::unchecked_copy<GameObject_*_*,GameObject_*_*>
          (GameObject **param_1,GameObject **param_2,GameObject **param_3)

{
  GameObject **ppGVar1;
  
  ppGVar1 = std::_Copy_opt<GameObject_*_*,GameObject_*_*,std::random_access_iterator_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Scalar_ptr_iterator_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppGVar1;
}
