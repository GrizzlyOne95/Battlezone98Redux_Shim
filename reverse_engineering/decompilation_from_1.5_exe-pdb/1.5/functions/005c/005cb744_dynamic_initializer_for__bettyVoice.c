/*
 * Entry: 005cb744
 * Name: `dynamic_initializer_for_'bettyVoice''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'bettyVoice''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__bettyVoice__(void)

{
  GameFeature::GameFeature((GameFeature *)&bettyVoice);
  bettyVoice._padding_ = (int)&BettyVoice::_vftable_;
  atexit(_dynamic_atexit_destructor_for__bettyVoice__);
  return;
}
