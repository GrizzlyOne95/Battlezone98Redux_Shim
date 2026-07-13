/*
 * Entry: 005cbb56
 * Name: `dynamic_initializer_for_'internalAdjuster''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'internalAdjuster''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__internalAdjuster__(void)

{
  InternalAdjuster::InternalAdjuster(&internalAdjuster);
  atexit(_dynamic_atexit_destructor_for__internalAdjuster__);
  return;
}
