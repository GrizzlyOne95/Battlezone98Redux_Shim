/*
 * Entry: 005cbb0f
 * Name: `dynamic_initializer_for_'flagDisplay''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'flagDisplay''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__flagDisplay__(void)

{
  GameFeature::GameFeature((GameFeature *)&flagDisplay);
  flagDisplay._padding_ = (int)&FlagDisplay::_vftable_;
  flagDisplay.flagTexture[0] = (TEXTURE *)0x0;
  flagDisplay.flagTexture[1] = (TEXTURE *)0x0;
  flagDisplay.flagTexture[2] = (TEXTURE *)0x0;
  atexit(_dynamic_atexit_destructor_for__flagDisplay__);
  return;
}
