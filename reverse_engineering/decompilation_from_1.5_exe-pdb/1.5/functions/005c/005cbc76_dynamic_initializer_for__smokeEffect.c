/*
 * Entry: 005cbc76
 * Name: `dynamic_initializer_for_'smokeEffect''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'smokeEffect''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__smokeEffect__(void)

{
  GameFeature::GameFeature((GameFeature *)&smokeEffect);
  smokeEffect._padding_ = (int)&SmokeEffect::_vftable_;
  atexit(_dynamic_atexit_destructor_for__smokeEffect__);
  return;
}
