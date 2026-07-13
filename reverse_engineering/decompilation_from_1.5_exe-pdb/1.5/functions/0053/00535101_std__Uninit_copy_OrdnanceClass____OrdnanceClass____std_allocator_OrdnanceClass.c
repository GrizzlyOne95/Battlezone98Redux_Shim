/*
 * Entry: 00535101
 * Name: std::_Uninit_copy<OrdnanceClass_*_*,OrdnanceClass_*_*,std::allocator<OrdnanceClass_*>_>
 * Namespace: std
 * Signature: OrdnanceClass * * _Uninit_copy<OrdnanceClass_*_*,OrdnanceClass_*_*,std::allocator<OrdnanceClass_*>_>(OrdnanceClass * * param_1, OrdnanceClass * * param_2, OrdnanceClass * * param_3, allocator<OrdnanceClass_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass ** __cdecl
std::_Uninit_copy<OrdnanceClass_*_*,OrdnanceClass_*_*,std::allocator<OrdnanceClass_*>_>
          (OrdnanceClass **param_1,OrdnanceClass **param_2,OrdnanceClass **param_3,
          allocator<OrdnanceClass_*> *param_4,_Scalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  int iVar1;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  if (iVar1 != 0) {
    memmove_s(param_3,iVar1 * 4,param_1,iVar1 * 4);
  }
  return param_3 + iVar1;
}
