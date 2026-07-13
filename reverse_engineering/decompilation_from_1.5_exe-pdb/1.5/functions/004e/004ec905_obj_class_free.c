/*
 * Entry: 004ec905
 * Name: obj_class_free
 * Namespace: Global
 * Signature: void obj_class_free(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* obj_class_free */

void __cdecl obj_class_free(void *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x004ec905. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  free(param_1);
  return;
}
