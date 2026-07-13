/*
 * Entry: 005152c7
 * Name: PREREQ_TestEquivalent
 * Namespace: Global
 * Signature: uchar PREREQ_TestEquivalent(ushort param_1, char param_2, ushort param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl PREREQ_TestEquivalent(ushort param_1,char param_2,ushort param_3)

{
  PREREQ_equiv *pPVar1;
  
  if (param_1 != param_3) {
    pPVar1 = PREREQ_table[param_1].equiv;
    while( true ) {
      if (pPVar1 == (PREREQ_equiv *)0x0) {
        return '\0';
      }
      if (pPVar1->type == param_3) break;
      pPVar1 = pPVar1->next;
    }
  }
  return '\x01';
}
