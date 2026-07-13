/*
 * Entry: 0052eac8
 * Name: std::_Uninit_copy<ExplosionClass_*_*,ExplosionClass_*_*,std::allocator<ExplosionClass_*>_>
 * Namespace: std
 * Signature: ExplosionClass * * _Uninit_copy<ExplosionClass_*_*,ExplosionClass_*_*,std::allocator<ExplosionClass_*>_>(ExplosionClass * * param_1, ExplosionClass * * param_2, ExplosionClass * * param_3, allocator<ExplosionClass_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ExplosionClass ** __cdecl
std::_Uninit_copy<ExplosionClass_*_*,ExplosionClass_*_*,std::allocator<ExplosionClass_*>_>
          (ExplosionClass **param_1,ExplosionClass **param_2,ExplosionClass **param_3,
          allocator<ExplosionClass_*> *param_4,_Scalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  int iVar1;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  if (iVar1 != 0) {
    memmove_s(param_3,iVar1 * 4,param_1,iVar1 * 4);
  }
  return param_3 + iVar1;
}
