/*
 * Entry: 0048694c
 * Name: std::_Uninit_copy<Craft_*_*,Craft_*_*,std::allocator<Craft_*>_>
 * Namespace: std
 * Signature: Craft * * _Uninit_copy<Craft_*_*,Craft_*_*,std::allocator<Craft_*>_>(Craft * * param_1, Craft * * param_2, Craft * * param_3, allocator<Craft_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Craft ** __cdecl
std::_Uninit_copy<Craft_*_*,Craft_*_*,std::allocator<Craft_*>_>
          (Craft **param_1,Craft **param_2,Craft **param_3,allocator<Craft_*> *param_4,
          _Scalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  int iVar1;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  if (iVar1 != 0) {
    memmove_s(param_3,iVar1 * 4,param_1,iVar1 * 4);
  }
  return param_3 + iVar1;
}
