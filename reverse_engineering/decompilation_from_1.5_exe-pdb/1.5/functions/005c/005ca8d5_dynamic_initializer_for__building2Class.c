/*
 * Entry: 005ca8d5
 * Name: `dynamic_initializer_for_'building2Class''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'building2Class''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__building2Class__(void)

{
  GameObjectClass::GameObjectClass((GameObjectClass *)&building2Class);
  building2Class._padding_ = (int)&BuildingClass::_vftable_;
  building2Class._padding_ = 0x424c4432;
  building2Class._padding_ = (int)s_i76building2;
  building2Class._padding_ = 10;
  building2Class.soundAmbient[0] = '\0';
  atexit(_dynamic_atexit_destructor_for__building2Class__);
  return;
}
