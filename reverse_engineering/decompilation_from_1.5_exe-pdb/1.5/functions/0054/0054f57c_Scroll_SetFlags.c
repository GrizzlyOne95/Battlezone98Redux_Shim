/*
 * Entry: 0054f57c
 * Name: Scroll_SetFlags
 * Namespace: Global
 * Signature: void Scroll_SetFlags(void * param_1, ulong param_2, ulong param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Scroll_SetFlags(void *param_1,ulong param_2,ulong param_3)

{
  *(ulong *)(*(int *)((int)param_1 + 8) + 0x60) =
       ~param_2 & *(uint *)(*(int *)((int)param_1 + 8) + 0x60) | param_2 & param_3;
  return;
}
