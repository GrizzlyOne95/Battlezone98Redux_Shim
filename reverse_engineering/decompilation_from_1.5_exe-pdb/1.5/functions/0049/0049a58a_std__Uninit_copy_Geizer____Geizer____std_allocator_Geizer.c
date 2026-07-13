/*
 * Entry: 0049a58a
 * Name: std::_Uninit_copy<Geizer_*_*,Geizer_*_*,std::allocator<Geizer_*>_>
 * Namespace: std
 * Signature: Geizer * * _Uninit_copy<Geizer_*_*,Geizer_*_*,std::allocator<Geizer_*>_>(Geizer * * param_1, Geizer * * param_2, Geizer * * param_3, allocator<Geizer_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Geizer ** __cdecl
std::_Uninit_copy<Geizer_*_*,Geizer_*_*,std::allocator<Geizer_*>_>
          (Geizer **param_1,Geizer **param_2,Geizer **param_3,allocator<Geizer_*> *param_4,
          _Scalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  int iVar1;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  if (iVar1 != 0) {
    memmove_s(param_3,iVar1 * 4,param_1,iVar1 * 4);
  }
  return param_3 + iVar1;
}
