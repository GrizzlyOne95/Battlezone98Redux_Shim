/*
 * Entry: 005ccc97
 * Name: `dynamic_atexit_destructor_for_'pathDisplay''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'pathDisplay''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__pathDisplay__(void)

{
  pathDisplay._padding_ = (int)&PathDisplay::_vftable_;
  DisplayInterface::~DisplayInterface((DisplayInterface *)&pathDisplay);
  return;
}
