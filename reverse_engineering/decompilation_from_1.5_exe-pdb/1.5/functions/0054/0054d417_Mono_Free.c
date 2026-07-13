/*
 * Entry: 0054d417
 * Name: Mono_Free
 * Namespace: Global
 * Signature: void Mono_Free(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mono_Free(long param_1)

{
  if (param_1 != 0) {
    *(undefined4 *)param_1 = 0;
  }
  return;
}
