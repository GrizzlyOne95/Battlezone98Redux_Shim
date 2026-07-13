/*
 * Entry: 005ccc3b
 * Name: `dynamic_atexit_destructor_for_'controlPanel''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'controlPanel''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__controlPanel__(void)

{
  controlPanel._padding_ = (int)&ControlPanel::_vftable_;
  DisplayInterface::~DisplayInterface((DisplayInterface *)&controlPanel);
  return;
}
