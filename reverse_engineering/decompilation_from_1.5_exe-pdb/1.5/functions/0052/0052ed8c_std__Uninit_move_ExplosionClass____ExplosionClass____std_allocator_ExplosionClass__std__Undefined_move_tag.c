/*
 * Entry: 0052ed8c
 * Name: std::_Uninit_move<ExplosionClass_*_*,ExplosionClass_*_*,std::allocator<ExplosionClass_*>,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: ExplosionClass * * _Uninit_move<ExplosionClass_*_*,ExplosionClass_*_*,std::allocator<ExplosionClass_*>,std::_Undefined_move_tag>(ExplosionClass * * param_1, ExplosionClass * * param_2, ExplosionClass * * param_3, allocator<ExplosionClass_*> * param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ExplosionClass ** __cdecl
std::
_Uninit_move<ExplosionClass_*_*,ExplosionClass_*_*,std::allocator<ExplosionClass_*>,std::_Undefined_move_tag>
          (ExplosionClass **param_1,ExplosionClass **param_2,ExplosionClass **param_3,
          allocator<ExplosionClass_*> *param_4,_Undefined_move_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  ExplosionClass **ppEVar1;
  
  ppEVar1 = stdext::
            unchecked_uninitialized_copy<ExplosionClass_*_*,ExplosionClass_*_*,std::allocator<ExplosionClass_*>_>
                      (param_1,param_2,param_3,param_4);
  return ppEVar1;
}
