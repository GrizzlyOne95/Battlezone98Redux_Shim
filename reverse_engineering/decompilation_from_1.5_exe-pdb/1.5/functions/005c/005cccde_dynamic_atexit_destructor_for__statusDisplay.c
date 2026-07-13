/*
 * Entry: 005cccde
 * Name: `dynamic_atexit_destructor_for_'statusDisplay''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'statusDisplay''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__statusDisplay__(void)

{
  statusDisplay._padding_ = (int)&StatusDisplay::_vftable_;
  DisplayInterface::~DisplayInterface((DisplayInterface *)&statusDisplay);
  return;
}
