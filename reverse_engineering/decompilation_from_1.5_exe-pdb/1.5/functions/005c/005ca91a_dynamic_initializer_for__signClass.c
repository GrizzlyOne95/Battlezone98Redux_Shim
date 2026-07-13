/*
 * Entry: 005ca91a
 * Name: `dynamic_initializer_for_'signClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'signClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__signClass__(void)

{
  GameObjectClass::GameObjectClass((GameObjectClass *)&signClass);
  signClass._padding_ = (int)&BuildingClass::_vftable_;
  signClass._padding_ = 0x5349474e;
  signClass._padding_ = (int)s_i76sign;
  signClass._padding_ = 5;
  signClass.soundAmbient[0] = '\0';
  atexit(_dynamic_atexit_destructor_for__signClass__);
  return;
}
