/*
 * Entry: 004adb8d
 * Name: std::_Uninit_copy<Scanner_*_*,Scanner_*_*,std::allocator<Scanner_*>_>
 * Namespace: std
 * Signature: Scanner * * _Uninit_copy<Scanner_*_*,Scanner_*_*,std::allocator<Scanner_*>_>(Scanner * * param_1, Scanner * * param_2, Scanner * * param_3, allocator<Scanner_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scanner ** __cdecl
std::_Uninit_copy<Scanner_*_*,Scanner_*_*,std::allocator<Scanner_*>_>
          (Scanner **param_1,Scanner **param_2,Scanner **param_3,allocator<Scanner_*> *param_4,
          _Scalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  int iVar1;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  if (iVar1 != 0) {
    memmove_s(param_3,iVar1 * 4,param_1,iVar1 * 4);
  }
  return param_3 + iVar1;
}
