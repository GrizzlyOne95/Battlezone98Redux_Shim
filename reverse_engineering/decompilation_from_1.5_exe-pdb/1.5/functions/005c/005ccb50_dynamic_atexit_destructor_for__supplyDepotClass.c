/*
 * Entry: 005ccb50
 * Name: `dynamic_atexit_destructor_for_'supplyDepotClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'supplyDepotClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__supplyDepotClass__(void)

{
  supplyDepotClass._padding_ = (int)&SupplyDepotClass::_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)&supplyDepotClass);
  return;
}
