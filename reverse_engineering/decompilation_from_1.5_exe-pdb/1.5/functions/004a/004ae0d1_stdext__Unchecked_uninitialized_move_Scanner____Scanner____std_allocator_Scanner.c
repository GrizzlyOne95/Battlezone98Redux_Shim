/*
 * Entry: 004ae0d1
 * Name: stdext::_Unchecked_uninitialized_move<Scanner_*_*,Scanner_*_*,std::allocator<Scanner_*>_>
 * Namespace: stdext
 * Signature: Scanner * * _Unchecked_uninitialized_move<Scanner_*_*,Scanner_*_*,std::allocator<Scanner_*>_>(Scanner * * param_1, Scanner * * param_2, Scanner * * param_3, allocator<Scanner_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scanner ** __cdecl
stdext::_Unchecked_uninitialized_move<Scanner_*_*,Scanner_*_*,std::allocator<Scanner_*>_>
          (Scanner **param_1,Scanner **param_2,Scanner **param_3,allocator<Scanner_*> *param_4)

{
  Scanner **ppSVar1;
  
  ppSVar1 = std::_Uninit_copy<Scanner_*_*,Scanner_*_*,std::allocator<Scanner_*>_>
                      (param_1,param_2,param_3,param_4,SUB41(param_2,0),
                       (_Range_checked_iterator_tag)0x0);
  return ppSVar1;
}
