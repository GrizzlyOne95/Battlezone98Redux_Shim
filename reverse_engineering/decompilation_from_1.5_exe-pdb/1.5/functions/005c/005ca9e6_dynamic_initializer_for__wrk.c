/*
 * Entry: 005ca9e6
 * Name: `dynamic_initializer_for_'wrk''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'wrk''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__wrk__(void)

{
  uint uVar1;
  
  uVar1 = __lzo_align_gap(wrkmem,0x10);
  wrk = wrkmem + uVar1;
  return;
}
