/*
 * Entry: 00525348
 * Name: freeBuf
 * Namespace: Global
 * Signature: void freeBuf(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl freeBuf(void *param_1)

{
  if (param_1 != (void *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0052534f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    free(param_1);
    return;
  }
  return;
}
