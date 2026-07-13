/*
 * Entry: 005cb7ee
 * Name: `dynamic_initializer_for_'hardPoints''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'hardPoints''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__hardPoints__(void)

{
  DisplayInterface::DisplayInterface((DisplayInterface *)&hardPoints);
  hardPoints._padding_ = (int)&HardPoints::_vftable_;
  hardPoints.showHardpoints = false;
  atexit(_dynamic_atexit_destructor_for__hardPoints__);
  return;
}
