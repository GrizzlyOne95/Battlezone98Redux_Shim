/*
 * Entry: 005152fc
 * Name: PREREQ_HaveEquivalent
 * Namespace: Global
 * Signature: uchar PREREQ_HaveEquivalent(ushort param_1, char param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl PREREQ_HaveEquivalent(ushort param_1,char param_2)

{
  PREREQ_equiv *pPVar1;
  
  if (PREREQ_table[param_1].howmany[param_2] < 1) {
    pPVar1 = PREREQ_table[param_1].equiv;
    while( true ) {
      if (pPVar1 == (PREREQ_equiv *)0x0) {
        return '\0';
      }
      if (0 < PREREQ_table[pPVar1->type].howmany[param_2]) break;
      pPVar1 = pPVar1->next;
    }
  }
  return '\x01';
}
