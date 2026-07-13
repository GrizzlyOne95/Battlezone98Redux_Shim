/*
 * Entry: 00451740
 * Name: std::_Uninit_fill_n<Strip_*_*,unsigned_int,Strip_*,std::allocator<Strip_*>_>
 * Namespace: std
 * Signature: void _Uninit_fill_n<Strip_*_*,unsigned_int,Strip_*,std::allocator<Strip_*>_>(Strip * * param_1, uint param_2, Strip * * param_3, allocator<Strip_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Uninit_fill_n<Strip_*_*,unsigned_int,Strip_*,std::allocator<Strip_*>_>
          (Strip **param_1,uint param_2,Strip **param_3,allocator<Strip_*> *param_4,
          _Scalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  for (; param_2 != 0; param_2 = param_2 - 1) {
    *param_1 = *param_3;
    param_1 = param_1 + 1;
  }
  return;
}
