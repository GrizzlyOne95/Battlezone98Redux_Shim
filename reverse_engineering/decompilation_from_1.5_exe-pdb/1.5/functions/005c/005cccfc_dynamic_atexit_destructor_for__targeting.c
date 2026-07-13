/*
 * Entry: 005cccfc
 * Name: `dynamic_atexit_destructor_for_'targeting''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'targeting''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__targeting__(void)

{
  targeting._0_4_ = &Targeting::_vftable_;
  DisplayInterface::~DisplayInterface((DisplayInterface *)&targeting);
  return;
}
