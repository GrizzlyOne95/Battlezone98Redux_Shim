/*
 * Entry: 004f3a52
 * Name: Font_Free
 * Namespace: Global
 * Signature: void Font_Free(FONT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Font_Free(FONT *param_1)

{
  if (hDefaultHeap != (void *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x004f3a5b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    free(param_1);
    return;
  }
  return;
}
