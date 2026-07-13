/*
 * Entry: 004ae0bc
 * Name: std::_Uninit_fill_n<Scanner_*_*,unsigned_int,Scanner_*,std::allocator<Scanner_*>_>
 * Namespace: std
 * Signature: void _Uninit_fill_n<Scanner_*_*,unsigned_int,Scanner_*,std::allocator<Scanner_*>_>(Scanner * * param_1, uint param_2, Scanner * * param_3, allocator<Scanner_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Uninit_fill_n<Scanner_*_*,unsigned_int,Scanner_*,std::allocator<Scanner_*>_>
          (Scanner **param_1,uint param_2,Scanner **param_3,allocator<Scanner_*> *param_4,
          _Scalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  stdext::unchecked_fill_n<Scanner_*_*,unsigned_int,Scanner_*>(param_1,param_2,param_3);
  return;
}
