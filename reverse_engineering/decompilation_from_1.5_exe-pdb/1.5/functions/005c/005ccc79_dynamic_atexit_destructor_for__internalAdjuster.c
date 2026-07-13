/*
 * Entry: 005ccc79
 * Name: `dynamic_atexit_destructor_for_'internalAdjuster''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'internalAdjuster''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__internalAdjuster__(void)

{
  InternalAdjuster::~InternalAdjuster(&internalAdjuster);
  return;
}
