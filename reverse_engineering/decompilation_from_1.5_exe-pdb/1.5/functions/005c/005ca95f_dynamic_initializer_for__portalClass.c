/*
 * Entry: 005ca95f
 * Name: `dynamic_initializer_for_'portalClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'portalClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__portalClass__(void)

{
  GameObjectClass::GameObjectClass((GameObjectClass *)&portalClass);
  portalClass._padding_ = (int)&BuildingClass::_vftable_;
  portalClass._padding_ = 0x504f5254;
  portalClass._padding_ = (int)s_portal;
  portalClass._padding_ = 2;
  portalClass.soundAmbient[0] = '\0';
  atexit(_dynamic_atexit_destructor_for__portalClass__);
  return;
}
