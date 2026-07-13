/*
 * Entry: 0048c9ad
 * Name: std::_Uninit_fill_n<BASE_STRUCT_*_*,unsigned_int,BASE_STRUCT_*,std::allocator<BASE_STRUCT_*>_>
 * Namespace: std
 * Signature: void _Uninit_fill_n<BASE_STRUCT_*_*,unsigned_int,BASE_STRUCT_*,std::allocator<BASE_STRUCT_*>_>(BASE_STRUCT * * param_1, uint param_2, BASE_STRUCT * * param_3, allocator<BASE_STRUCT_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Uninit_fill_n<BASE_STRUCT_*_*,unsigned_int,BASE_STRUCT_*,std::allocator<BASE_STRUCT_*>_>
          (BASE_STRUCT **param_1,uint param_2,BASE_STRUCT **param_3,
          allocator<BASE_STRUCT_*> *param_4,_Scalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  stdext::unchecked_fill_n<BASE_STRUCT_*_*,unsigned_int,BASE_STRUCT_*>(param_1,param_2,param_3);
  return;
}
