/*
 * Entry: 00515417
 * Name: PREREQ_Prune
 * Namespace: Global
 * Signature: void PREREQ_Prune(ushort * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PREREQ_Prune(ushort *param_1)

{
  while (*param_1 != 0) {
    *param_1 = param_1[1];
    param_1 = param_1 + 1;
  }
  return;
}
