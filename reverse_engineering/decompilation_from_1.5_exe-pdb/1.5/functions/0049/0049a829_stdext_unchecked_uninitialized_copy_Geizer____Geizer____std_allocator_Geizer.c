/*
 * Entry: 0049a829
 * Name: stdext::unchecked_uninitialized_copy<Geizer_*_*,Geizer_*_*,std::allocator<Geizer_*>_>
 * Namespace: stdext
 * Signature: Geizer * * unchecked_uninitialized_copy<Geizer_*_*,Geizer_*_*,std::allocator<Geizer_*>_>(Geizer * * param_1, Geizer * * param_2, Geizer * * param_3, allocator<Geizer_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Geizer ** __cdecl
stdext::unchecked_uninitialized_copy<Geizer_*_*,Geizer_*_*,std::allocator<Geizer_*>_>
          (Geizer **param_1,Geizer **param_2,Geizer **param_3,allocator<Geizer_*> *param_4)

{
  Geizer **ppGVar1;
  
  ppGVar1 = std::_Uninit_copy<Geizer_*_*,Geizer_*_*,std::allocator<Geizer_*>_>
                      (param_1,param_2,param_3,param_4,SUB41(param_2,0),
                       (_Range_checked_iterator_tag)0x0);
  return ppGVar1;
}
