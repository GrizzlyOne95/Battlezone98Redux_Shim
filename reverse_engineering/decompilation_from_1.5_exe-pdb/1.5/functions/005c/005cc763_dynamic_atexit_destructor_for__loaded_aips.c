/*
 * Entry: 005cc763
 * Name: `dynamic_atexit_destructor_for_'loaded_aips''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'loaded_aips''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__loaded_aips__(void)

{
  ExpandingArray<_loaded_aip>::Clear(&loaded_aips);
  return;
}
