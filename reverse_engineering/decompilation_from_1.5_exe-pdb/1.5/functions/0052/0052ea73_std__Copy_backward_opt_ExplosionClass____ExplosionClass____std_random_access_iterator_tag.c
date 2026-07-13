/*
 * Entry: 0052ea73
 * Name: std::_Copy_backward_opt<ExplosionClass_*_*,ExplosionClass_*_*,std::random_access_iterator_tag>
 * Namespace: std
 * Signature: ExplosionClass * * _Copy_backward_opt<ExplosionClass_*_*,ExplosionClass_*_*,std::random_access_iterator_tag>(ExplosionClass * * param_1, ExplosionClass * * param_2, ExplosionClass * * param_3, random_access_iterator_tag param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ExplosionClass ** __cdecl
std::_Copy_backward_opt<ExplosionClass_*_*,ExplosionClass_*_*,std::random_access_iterator_tag>
          (ExplosionClass **param_1,ExplosionClass **param_2,ExplosionClass **param_3,
          random_access_iterator_tag param_4,_Scalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  int iVar1;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  if (0 < iVar1) {
    memmove_s(param_3 + -iVar1,iVar1 * 4,param_1,iVar1 * 4);
  }
  return param_3 + -iVar1;
}
