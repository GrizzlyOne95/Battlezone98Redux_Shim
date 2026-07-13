/*
 * Entry: 0052ed3a
 * Name: std::fill<ExplosionClass_*_*,ExplosionClass_*>
 * Namespace: std
 * Signature: void fill<ExplosionClass_*_*,ExplosionClass_*>(ExplosionClass * * param_1, ExplosionClass * * param_2, ExplosionClass * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::fill<ExplosionClass_*_*,ExplosionClass_*>
          (ExplosionClass **param_1,ExplosionClass **param_2,ExplosionClass **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
