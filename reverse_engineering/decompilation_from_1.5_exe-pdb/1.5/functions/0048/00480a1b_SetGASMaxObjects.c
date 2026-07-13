/*
 * Entry: 00480a1b
 * Name: SetGASMaxObjects
 * Namespace: Global
 * Signature: void SetGASMaxObjects(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetGASMaxObjects(long param_1)

{
  if (GM != (GAS_MASTER *)0x0) {
    GM->maxObjects = param_1;
  }
  return;
}
