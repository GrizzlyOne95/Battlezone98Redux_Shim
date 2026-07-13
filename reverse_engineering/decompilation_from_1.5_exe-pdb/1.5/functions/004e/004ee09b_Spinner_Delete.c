/*
 * Entry: 004ee09b
 * Name: Spinner_Delete
 * Namespace: Global
 * Signature: void Spinner_Delete(SPINNER * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Spinner_Delete(SPINNER *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x004ec905. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  free(param_1);
  return;
}
