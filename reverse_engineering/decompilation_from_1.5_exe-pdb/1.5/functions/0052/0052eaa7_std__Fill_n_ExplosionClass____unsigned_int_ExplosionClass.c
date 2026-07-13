/*
 * Entry: 0052eaa7
 * Name: std::_Fill_n<ExplosionClass_*_*,unsigned_int,ExplosionClass_*>
 * Namespace: std
 * Signature: void _Fill_n<ExplosionClass_*_*,unsigned_int,ExplosionClass_*>(ExplosionClass * * param_1, uint param_2, ExplosionClass * * param_3, _Range_checked_iterator_tag param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Fill_n<ExplosionClass_*_*,unsigned_int,ExplosionClass_*>
          (ExplosionClass **param_1,uint param_2,ExplosionClass **param_3,
          _Range_checked_iterator_tag param_4)

{
  for (; param_2 != 0; param_2 = param_2 - 1) {
    *param_1 = *param_3;
    param_1 = param_1 + 1;
  }
  return;
}
