/*
 * Entry: 0052ee5a
 * Name: stdext::_Unchecked_uninitialized_move<ExplosionClass_*_*,ExplosionClass_*_*,std::allocator<ExplosionClass_*>_>
 * Namespace: stdext
 * Signature: ExplosionClass * * _Unchecked_uninitialized_move<ExplosionClass_*_*,ExplosionClass_*_*,std::allocator<ExplosionClass_*>_>(ExplosionClass * * param_1, ExplosionClass * * param_2, ExplosionClass * * param_3, allocator<ExplosionClass_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ExplosionClass ** __cdecl
stdext::
_Unchecked_uninitialized_move<ExplosionClass_*_*,ExplosionClass_*_*,std::allocator<ExplosionClass_*>_>
          (ExplosionClass **param_1,ExplosionClass **param_2,ExplosionClass **param_3,
          allocator<ExplosionClass_*> *param_4)

{
  ExplosionClass **ppEVar1;
  
  ppEVar1 = std::
            _Uninit_copy<ExplosionClass_*_*,ExplosionClass_*_*,std::allocator<ExplosionClass_*>_>
                      (param_1,param_2,param_3,param_4,SUB41(param_2,0),
                       (_Range_checked_iterator_tag)0x0);
  return ppEVar1;
}
