/*
 * Entry: 005cca6e
 * Name: `dynamic_atexit_destructor_for_'repairDepotClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'repairDepotClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__repairDepotClass__(void)

{
  repairDepotClass._padding_ = (int)&RepairDepotClass::_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)&repairDepotClass);
  return;
}
