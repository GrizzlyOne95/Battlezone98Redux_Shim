/*
 * Entry: 0052ed67
 * Name: stdext::unchecked_fill_n<ExplosionClass_*_*,unsigned_int,ExplosionClass_*>
 * Namespace: stdext
 * Signature: void unchecked_fill_n<ExplosionClass_*_*,unsigned_int,ExplosionClass_*>(ExplosionClass * * param_1, uint param_2, ExplosionClass * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::unchecked_fill_n<ExplosionClass_*_*,unsigned_int,ExplosionClass_*>
          (ExplosionClass **param_1,uint param_2,ExplosionClass **param_3)

{
  std::_Fill_n<ExplosionClass_*_*,unsigned_int,ExplosionClass_*>
            (param_1,param_2,param_3,(random_access_iterator_tag)0x0,
             (_Range_checked_iterator_tag)0x0);
  return;
}
