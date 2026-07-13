/*
 * Entry: 00515780
 * Name: PREREQ_PruneDuplicates
 * Namespace: Global
 * Signature: void PREREQ_PruneDuplicates(ushort * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PREREQ_PruneDuplicates(ushort *param_1)

{
  ushort *puVar1;
  ushort *puVar2;
  
  while (puVar2 = param_1, puVar1 = puVar2 + 1, *puVar2 != 0) {
    while (param_1 = puVar2 + 1, *puVar1 != 0) {
      if (*puVar2 == *puVar1) {
        PREREQ_Prune(puVar1);
      }
      else {
        puVar1 = puVar1 + 1;
      }
    }
  }
  return;
}
