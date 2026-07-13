/*
 * Entry: 00515244
 * Name: PREREQ_HowManyEquivalent
 * Namespace: Global
 * Signature: int PREREQ_HowManyEquivalent(ushort param_1, char param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl PREREQ_HowManyEquivalent(ushort param_1,char param_2)

{
  ushort *puVar1;
  int iVar2;
  PREREQ_equiv *pPVar3;
  
  pPVar3 = PREREQ_table[param_1].equiv;
  iVar2 = 0;
  if (pPVar3 == (PREREQ_equiv *)0x0) {
    return PREREQ_table[param_1].howmany[param_2];
  }
  do {
    puVar1 = &pPVar3->type;
    pPVar3 = pPVar3->next;
    iVar2 = iVar2 + PREREQ_table[*puVar1].howmany[param_2];
  } while (pPVar3 != (PREREQ_equiv *)0x0);
  return iVar2;
}
