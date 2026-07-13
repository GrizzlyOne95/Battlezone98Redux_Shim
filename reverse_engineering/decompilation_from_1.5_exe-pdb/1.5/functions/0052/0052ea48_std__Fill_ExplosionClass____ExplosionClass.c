/*
 * Entry: 0052ea48
 * Name: std::_Fill<ExplosionClass_*_*,ExplosionClass_*>
 * Namespace: std
 * Signature: void _Fill<ExplosionClass_*_*,ExplosionClass_*>(ExplosionClass * * param_1, ExplosionClass * * param_2, ExplosionClass * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Fill<ExplosionClass_*_*,ExplosionClass_*>
          (ExplosionClass **param_1,ExplosionClass **param_2,ExplosionClass **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
