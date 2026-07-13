/*
 * Entry: 0044ff90
 * Name: std::_Uninit_copy<Strip_*_*,Strip_*_*,std::allocator<Strip_*>_>
 * Namespace: std
 * Signature: Strip * * _Uninit_copy<Strip_*_*,Strip_*_*,std::allocator<Strip_*>_>(Strip * * param_1, Strip * * param_2, Strip * * param_3, allocator<Strip_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Strip ** __cdecl
std::_Uninit_copy<Strip_*_*,Strip_*_*,std::allocator<Strip_*>_>
          (Strip **param_1,Strip **param_2,Strip **param_3,allocator<Strip_*> *param_4,
          _Scalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  int iVar1;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  if (iVar1 != 0) {
    memmove_s(param_3,iVar1 * 4,param_1,iVar1 * 4);
  }
  return param_3 + iVar1;
}
