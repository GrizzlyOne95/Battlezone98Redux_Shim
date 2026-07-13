/*
 * Entry: 00484258
 * Name: mw2free
 * Namespace: Global
 * Signature: void mw2free(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* void __cdecl mw2free(void *) */

void __cdecl mw2free(void *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00484258. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  free(param_1);
  return;
}
