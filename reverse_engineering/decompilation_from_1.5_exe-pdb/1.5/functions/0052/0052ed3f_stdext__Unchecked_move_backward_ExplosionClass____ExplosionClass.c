/*
 * Entry: 0052ed3f
 * Name: stdext::_Unchecked_move_backward<ExplosionClass_*_*,ExplosionClass_*_*>
 * Namespace: stdext
 * Signature: ExplosionClass * * _Unchecked_move_backward<ExplosionClass_*_*,ExplosionClass_*_*>(ExplosionClass * * param_1, ExplosionClass * * param_2, ExplosionClass * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ExplosionClass ** __cdecl
stdext::_Unchecked_move_backward<ExplosionClass_*_*,ExplosionClass_*_*>
          (ExplosionClass **param_1,ExplosionClass **param_2,ExplosionClass **param_3)

{
  ExplosionClass **ppEVar1;
  
  ppEVar1 = std::
            _Move_backward_opt<ExplosionClass_*_*,ExplosionClass_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Undefined_move_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppEVar1;
}
