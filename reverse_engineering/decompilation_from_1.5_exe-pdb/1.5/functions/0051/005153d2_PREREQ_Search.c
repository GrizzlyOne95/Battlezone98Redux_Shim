/*
 * Entry: 005153d2
 * Name: PREREQ_Search
 * Namespace: Global
 * Signature: void PREREQ_Search(ushort param_1, ushort * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PREREQ_Search(ushort param_1,ushort **param_2)

{
  ushort uVar1;
  ushort *puVar2;
  
  puVar2 = PREREQ_table[param_1].prereqs;
  while( true ) {
    uVar1 = *puVar2;
    if (uVar1 == 0) break;
    if (uVar1 != param_1) {
      PREREQ_Search(uVar1,param_2);
    }
    puVar2 = puVar2 + 1;
  }
  **param_2 = param_1;
  *param_2 = *param_2 + 1;
  return;
}
