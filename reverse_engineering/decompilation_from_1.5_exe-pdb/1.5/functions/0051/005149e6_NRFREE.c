/*
 * Entry: 005149e6
 * Name: NRFREE
 * Namespace: Global
 * Signature: void NRFREE(void * _Memory)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl NRFREE(void *_Memory)

{
                    /* WARNING: Could not recover jumptable at 0x005149e6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  free(_Memory);
  return;
}
