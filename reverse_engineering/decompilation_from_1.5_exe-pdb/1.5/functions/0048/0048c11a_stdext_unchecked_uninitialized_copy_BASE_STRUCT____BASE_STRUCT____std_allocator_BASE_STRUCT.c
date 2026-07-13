/*
 * Entry: 0048c11a
 * Name: stdext::unchecked_uninitialized_copy<BASE_STRUCT_*_*,BASE_STRUCT_*_*,std::allocator<BASE_STRUCT_*>_>
 * Namespace: stdext
 * Signature: BASE_STRUCT * * unchecked_uninitialized_copy<BASE_STRUCT_*_*,BASE_STRUCT_*_*,std::allocator<BASE_STRUCT_*>_>(BASE_STRUCT * * param_1, BASE_STRUCT * * param_2, BASE_STRUCT * * param_3, allocator<BASE_STRUCT_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BASE_STRUCT ** __cdecl
stdext::unchecked_uninitialized_copy<BASE_STRUCT_*_*,BASE_STRUCT_*_*,std::allocator<BASE_STRUCT_*>_>
          (BASE_STRUCT **param_1,BASE_STRUCT **param_2,BASE_STRUCT **param_3,
          allocator<BASE_STRUCT_*> *param_4)

{
  BASE_STRUCT **ppBVar1;
  
  ppBVar1 = std::_Uninit_copy<BASE_STRUCT_*_*,BASE_STRUCT_*_*,std::allocator<BASE_STRUCT_*>_>
                      (param_1,param_2,param_3,param_4,SUB41(param_2,0),
                       (_Range_checked_iterator_tag)0x0);
  return ppBVar1;
}
