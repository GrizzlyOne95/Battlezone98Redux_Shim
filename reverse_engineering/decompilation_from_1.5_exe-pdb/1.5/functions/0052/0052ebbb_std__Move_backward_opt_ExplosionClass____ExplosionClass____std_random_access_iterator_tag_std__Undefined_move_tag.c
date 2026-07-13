/*
 * Entry: 0052ebbb
 * Name: std::_Move_backward_opt<ExplosionClass_*_*,ExplosionClass_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: ExplosionClass * * _Move_backward_opt<ExplosionClass_*_*,ExplosionClass_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>(ExplosionClass * * param_1, ExplosionClass * * param_2, ExplosionClass * * param_3, random_access_iterator_tag param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ExplosionClass ** __cdecl
std::
_Move_backward_opt<ExplosionClass_*_*,ExplosionClass_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
          (ExplosionClass **param_1,ExplosionClass **param_2,ExplosionClass **param_3,
          random_access_iterator_tag param_4,_Undefined_move_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  ExplosionClass **ppEVar1;
  
  ppEVar1 = _Copy_backward_opt<ExplosionClass_*_*,ExplosionClass_*_*,std::random_access_iterator_tag>
                      (param_1,param_2,param_3,param_4,(_Scalar_ptr_iterator_tag)0x0,
                       (_Range_checked_iterator_tag)0x0);
  return ppEVar1;
}
